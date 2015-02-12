/**
 * \file sample.h
 *
 * \ingroup BryceDirt
 * 
 * \brief Class def header for a class sample
 *
 * @author brycelittlejohn
 */

/** \addtogroup BryceDirt

    @{*/
#ifndef BRYCEWORK_BRYCEDIRT_SAMPLE_H
#define BRYCEWORK_BRYCEDIRT_SAMPLE_H

#include <iostream>

/**
   \class sample
   User defined class BryceDirt ... these comments are used to generate
   doxygen documentation!
 */
class sample{

public:

  /// Default constructor
  sample(){}

  /// Default destructor
  virtual ~sample(){};
  
  void HelloWorld(){std::cout<<"Hello World!"<<std::endl;}

};

#endif
/** @} */ // end of doxygen group 

