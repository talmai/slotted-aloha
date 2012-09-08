/*
  author: talmai.oliveira (talmai@talmai.com.br)
  file: packet.hpp
  This class is a wrapper to help simplify the handling of the
  data generated from the simulation. In this case, we are
  simplifying the concept of packets that will be sent by
  the clients.
*/

#ifndef PACKET_HPP
#define PACKET_HPP

class Packet {
	int id_;

	char type_;
	char status_;

	double schedule_time_;
	double first_schedule_time_;
	double first_send_attempt_;
	double sent_time_;
	double expected_receive_time_;
	double receive_time_;

	int num_retransmission_attempts_;

	int from_;
	int to_;
	int payload_;

public:
	Packet() : 	id_(-1),
				type_(Packet::UNDEFINED()),
				status_(Packet::UNDEFINED()),
				schedule_time_(-1),
				first_schedule_time_(-1),
				first_send_attempt_(-1),
				sent_time_(-1),
				expected_receive_time_(-1),
				receive_time_(-1),
				num_retransmission_attempts_(0),
				from_(-1),
				to_(-1),
				payload_(-1){};

	/* pseudo-constants */
	static char MSG() 					{ return 0x00; }; /* 0000 0000 */
	static char ACK() 					{ return 0x10; }; /* 0001 0000 */
	static char UNDEFINED() 			{ return 0x20; }; /* 0010 0000 */
	static char SENDING() 				{ return 0x30; }; /* 0011 0000 */
	static char RECEIVED() 				{ return 0x40; }; /* 0100 0000 */
	static char SCHEDULED() 			{ return 0x50; }; /* 0101 0000 */
	static char ACKNOWLEDGED() 			{ return 0x60; }; /* 0110 0000 */

	/* getters and setters */
	void set_id(int i) { id_ = i; }
	int get_id()  const { return id_; }

	void set_type(char c) { type_ = c; }
	char get_type()  const { return type_; }

	void set_status(char c) { status_ = c; }
	char get_status()  const { return status_; }

	void set_schedule_time(double t) { schedule_time_ = t; }
	double get_schedule_time()  const { return schedule_time_; }

	void set_first_schedule_time(double t) { first_schedule_time_ = t; }
	double get_first_schedule_time()  const { return first_schedule_time_; }

	void set_expected_receive_time(double t) { expected_receive_time_ = t; }
	double get_expected_receive_time()  const { return expected_receive_time_; }

	void set_to(int i) { to_ = i; }
	int get_to()  const { return to_; }

	void set_from(int i) { from_ = i; }
	int get_from()  const { return from_; }

	void set_payload(int i) { payload_ = i; }
	int get_payload() const { return payload_; }

	/* Method declaration */
	void sent(double time);
	void received(double time);
	void output() const;
	double get_effective_transmission_time() const;
	double get_total_transmission_time() const;
	double get_total_delay() const;
};

#endif
