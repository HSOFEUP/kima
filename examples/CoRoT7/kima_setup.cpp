#include <iostream>
#include "DNest4.h"
#include "Data.h"
#include "RVmodel.h"

using namespace std;
using namespace DNest4;

/* priors */
//  data-dependent priors should be defined in the RVmodel() 
//  constructor and use Data::get_instance() 
#include "default_priors.h"

const bool obs_after_HARPS_fibers = false;
const bool GP = true;
const bool hyperpriors = false;
const bool trend = false;
const bool multi_instrument = false;

// options for the model
// 
RVmodel::RVmodel()
    :planets(5, 5, false, RVConditionalPrior())
    ,mu(Data::get_instance().N())
    ,C(Data::get_instance().N(), Data::get_instance().N())
{
    double ymin = Data::get_instance().get_y_min();
    double ymax = Data::get_instance().get_y_max();
    // can now use ymin and ymax in setting prior for vsys
    Cprior = new Uniform(ymin, ymax);

    save_setup();
}


int main(int argc, char** argv)
{
    /* set the RV data file */
    // kima skips the first 2 lines in the header
    // and reads the first 3 columns into time, vrad and svrad
    char* datafile = "corot7.txt";

    Data::get_instance().load(datafile, "ms");
    
    // set the sampler and run it!
    Sampler<RVmodel> sampler = setup<RVmodel>(argc, argv);
    sampler.run();

    return 0;
}
