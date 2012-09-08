/*
  author: talmai.oliveira (talmai@talmai.com.br)
  file: packet.cpp
  This class is a wrapper to help simplify the handling of the
  data generated from the simulation. In this case, we are
  simplifying the concept of packets that will be sent by
  the clients.
 */

using namespace std;

/* Required header files */
#include <packet.hpp>
#include <iostream>

void Packet::sent(double time)
{
	if (first_send_attempt_ == -1)
	{
		first_send_attempt_ = time;
	}
	num_retransmission_attempts_++;
	sent_time_ = time;
	status_ = Packet::SENDING();
}

void Packet::received(double time)
{
	receive_time_ = time;
	status_ = Packet::RECEIVED();
}

void Packet::output() const{
	cout << "PACKET: " << id_ << " from NODE: " << from_ << " [SCH]" << schedule_time_ << " [FIRS]" << first_send_attempt_ << " [SENT]" << sent_time_
		<< " [XP_RCV]" << expected_receive_time_ << " [RCV]" << receive_time_ << " [ATMPT]" << num_retransmission_attempts_ << " [STAT]";
	if (status_ == SENDING()) cout << " sending" << endl;
	if (status_ == RECEIVED()) cout << " received" << endl;
	if (status_ == SCHEDULED()) cout << " scheduled" << endl;
	if (status_ == ACKNOWLEDGED()) cout << " acknowledged" << endl;
}

double Packet::get_effective_transmission_time() const {
	return receive_time_ - sent_time_;
}

double Packet::get_total_transmission_time() const {
	return receive_time_ - first_send_attempt_;
}

double Packet::get_total_delay() const {
	return receive_time_ - first_schedule_time_;
}
