/*
  author: talmai.oliveira (talmai@talmai.com.br)
  file: random_number_generator.hpp
  A uniformly distributed random number generator and
  exponentially distributed random variate generator.
  Contains method that is capable of generating log
  for tests and analysis.
*/

#ifndef RANDOM_NUMBER_GENERATOR_HPP
#define RANDOM_NUMBER_GENERATOR_HPP

/* Header files needed for this program */
#include <iostream>
#include <cmath>
#include <fstream>

class Random_Number_Generator {
	double seed_;
	double rate_; 
	double previous_number_;
	/* LCG values */
    int M; // 2^31 -1 = 2147483647
    int a; // 8*8192+3 = 65539

public:
	Random_Number_Generator() : seed_(1234.0), rate_(-1), previous_number_(1),
	                            M(2147483648), a(65539)
    {
        /* initialize random seed: */
        srand ((int)seed_);
    };

   	/* getters and setters */
   	void set_seed(double d) { seed_ = d; srand ((int)seed_); previous_number_ = seed_; };
   	double get_seed() const { return seed_; };
   	void set_rate(double d) { rate_ = d; };
   	double get_rate() const { return rate_; };
   	
   	void output()
   	{
   	     cout << "*** Random_Number_Generator ***" << endl
                 << "seed " << seed_ << endl
                 << "rate " << rate_ << endl;	     
   	};

    double next()
    {
      previous_number_ = fmod((a * previous_number_), M);
      return previous_number_;
    }

    double next_normalized()
    {
      previous_number_ = fmod((a * previous_number_), M);
      return -previous_number_/M;
    }

    double exponential(double n)
    {
      // calculating F'(x) - using inverse transformation of exponential pdf
      return (-1/rate_) * log(1-n);
    }
	
    double exponential()
    {
      // calculating F'(x) - using inverse transformation of exponential pdf
      return (-1/rate_) * log(1-next_normalized());
    }


    double rand_exponential()
    {
      double rnd = rand()/(double)RAND_MAX;
      return (-1/rate_) * log(1-rnd);
    }
    
    void test()
    {
        ofstream outFile;

        outFile.open("rnd_01.txt", ios::out);
        outFile.precision(6);
        set_seed(1);
        for (int i = 0; i < 10000; i++) 
        {
            outFile << fixed << exponential() << endl;
        }
        outFile << fixed << exponential();
        outFile.close();

        outFile.open("rnd_02.txt", ios::out);
        outFile.precision(6);
        set_seed(7.51391e+008);
        for (int i = 0; i < 10000; i++) 
        {
            outFile << fixed << exponential() << endl;
        }
        outFile << fixed << exponential();
        outFile.close();

        outFile.open("rnd_03.txt", ios::out);
        outFile.precision(6);
        set_seed(5.648e+008);
        for (int i = 0; i < 10000; i++) 
        {
            outFile << fixed << exponential() << endl;
        }
        outFile << fixed << exponential();
        outFile.close();
        
        outFile.open("rnd_04.txt", ios::out);
        outFile.precision(6);
        set_seed(1234);
        for (int i = 0; i < 10000; i++) 
        {
            outFile << fixed << rand_exponential() << endl;
        }
        outFile << fixed << rand_exponential();
        outFile.close();
        
    }
};

#endif
