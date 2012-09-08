/*
  author: talmai.oliveira (talmai@talmai.com.br)
  file: mm1_queue.cpp
  A MM1 queue object that, given lambda and mu, is capable
  of simulating a queue and evaluating results. This object
  can also be "plugged" in sequentially, creating queues
  that "feed" each other.
*/

using namespace std;

#include <wireless_node.hpp>

/*
  Used to create a new packet
*/
Packet Wireless_node::create_new_packet(char type, int to, double current_time)
{
	Packet pkt;
	pkt.set_id(generated_packets_++);
	pkt.set_type(type);
	pkt.set_status(Packet::SCHEDULED());
	pkt.set_from(id_);
	pkt.set_to(to);
	pkt.set_first_schedule_time(current_time + rnd_transmission.exponential());
	pkt.set_schedule_time(pkt.get_first_schedule_time());
	pkt.set_expected_receive_time(pkt.get_schedule_time()+propagation_time_);
	return pkt;
}

Packet Wireless_node::create_new_msg_packet(int to, double current_time)
{
	return create_new_packet(Packet::MSG(), to, current_time);
}

Packet Wireless_node::create_new_ack_packet(int to, double current_time, int pkt_id)
{
	Packet p = create_new_packet(Packet::ACK(), to, current_time);
	p.set_payload(pkt_id);
	return p;
}

/*
  Sets the seed of the random variables
*/
void Wireless_node::set_seed(double trans)
{
     rnd_transmission.set_seed(trans);
}

/*
  Creates instances of the Random Variate Generator and
  also the first event...
*/
void Wireless_node::initialize()
{
	if (!initialized_) {
		rnd_transmission.set_rate(transmission_rate_);
		initialized_ = true;
	}
}

void Wireless_node::output() const{
//	cout << "NODE: " << id_ << " [COMP]" << completed_transmissions_ << " [ATMPT]" << attempted_transmissions_ << " [FAIL]" << failed_transmissions_
//		<< " [GEN]" << generated_packets_ << " [EFF]" << efficiency_ << "( " << transmission_rate_ * propagation_time_ << ") [DELAY]"  << delay_/generated_packets_ << endl;
	cout << "NODE: " << id_ << " [Completed transmissions]" << completed_transmissions_ << " [# Transmission attempts]" << attempted_transmissions_
			<< " [Throughput]" << efficiency_ << " [G]" << transmission_rate_ * propagation_time_ << " [Average Delay]"  << delay_/generated_packets_ << endl;
}

void Wireless_node::attempt_transmission(Packet *p, double current_time) {
	attempted_transmissions_++;
	p->sent(current_time);
}

void Wireless_node::completed_transmission(Packet *p, double current_time) {
	completed_transmissions_++;
	p->received(current_time);
	efficiency_ += p->get_effective_transmission_time()/p->get_total_transmission_time();
	efficiency_ = efficiency_ / 2;
	delay_ += p->get_total_delay();
}

void Wireless_node::reschedule_packet(Packet *p, double time)
{
	p->set_status(Packet::SCHEDULED());
	if (p->get_first_schedule_time()==-1)
	{
		p->set_first_schedule_time(p->get_schedule_time());
	}
	p->set_schedule_time(time);
	p->set_expected_receive_time(p->get_schedule_time()+propagation_time_);
}

void Wireless_node::collision(Packet *p, double current_time) {
	failed_transmissions_++;
	reschedule_packet(p, current_time + rnd_transmission.exponential());
}

/* this next method returns TRUE if the simulation is within the desired error range */
bool Wireless_node::is_within_error_range(double err) const {
	return (efficiency_ > 0) && (abs(efficiency_ - get_expected_efficiency()) < err);
}

double Wireless_node::get_expected_efficiency() const {
	double G = transmission_rate_ * propagation_time_;
	return G*exp(eff_factor_*G);
}
