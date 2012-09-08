/*
 author: talmai.oliveira (talmai@talmai.com.br)
 file: wireless_node.hpp
 A wireless node object that, given packet transmission rate lambda,
 is capable of simulating a ALOHA/SLOTTED_ALOHA client and generate
 statistics for posterior evaluation of results.
 */

#ifndef WIRELESS_NODE_HPP
#define WIRELESS_NODE_HPP

/* Header files needed for this program */
#include <iostream>
#include <vector>
#include <string>
#include <packet.hpp>
#include <random_number_generator.hpp>
#include <fstream>
#include <cmath>

class Wireless_node {
	int id_;
	/*
	 These variables are used to evaluate the performance of
	 the node during or at the end of the simulation
	 */
	int completed_transmissions_; // total number of transmissions completed
	int attempted_transmissions_; // total number of attempted transmissions
	int failed_transmissions_; // total number of failed transmission attempts
	int generated_packets_; // total number of generated packets

	double efficiency_;
	double delay_;
	int eff_factor_;

	/*
	 These variables are used for the simulation of the node
	 */
	Random_Number_Generator rnd_transmission;
	double transmission_rate_;
	double propagation_time_;
	bool initialized_;

private:
	Packet create_new_packet(char type, int to, double current_time);

public:
	Wireless_node() :
		completed_transmissions_(0), attempted_transmissions_(0),
				failed_transmissions_(0), generated_packets_(0),
				efficiency_(1), delay_(0), eff_factor_(1),
				transmission_rate_(100), propagation_time_(0.01), initialized_(false) {};

	/* Getters and Setters */
	double get_completed_transmissions() const {
		return completed_transmissions_;
	};

	double get_attempted_transmissions() const {
		return attempted_transmissions_;
	};

	double get_efficiency() const {
		return efficiency_;
	};

	double get_average_delay() const {
		return delay_/generated_packets_;
	};

	void set_eff_factor(int i) {
		eff_factor_ = i;
	};

	void set_id(int i) {
		id_ = i;
	};

	int get_id() const {
		return id_;
	};

	void set_transmission_rate(double d) {
		transmission_rate_ = d;
	};

	double get_transmission_rate() const {
		return transmission_rate_;
	};

	void set_propagation_time(double d) {
		propagation_time_ = d;
	};

	double get_propagation_time() const {
		return propagation_time_;
	};

	/* definition of remaining public functions */
	void initialize();
	Packet create_new_msg_packet(int to, double current_time);
	Packet create_new_ack_packet(int to, double current_time, int pkt_id);
	void attempt_transmission(Packet *p, double current_time);
	void completed_transmission(Packet *p, double current_time);
	void collision(Packet *p, double current_time);
	void reschedule_packet(Packet *p, double exact_time);
	void set_seed(double transmission);
	void output() const;
	bool is_within_error_range(double err) const;
	double get_expected_efficiency() const;

};

#endif
