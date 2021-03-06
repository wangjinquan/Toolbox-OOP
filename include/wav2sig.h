#ifndef WAV2SIG_H
#define WAV2SIG_H

#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdexcept>
#include <algorithm>
#include "armadillo"
#include "AudioFile.h"
#include "sigpack.h"

using namespace arma;

class wav2sig {
private:
    std::vector<std::string> fnames;              //filenames
    uint8_t                  num_files;           //number of files
    float                    fs;                  //resample file to this frequency
    std::vector<float>       tInt;                //time interval (in seconds)
    std::vector<int>         samples_per_channel;
    std::vector<int>         channel_fs;          //fs for each channel
    std::vector<double>      weights;             //n weights, as many as there are files, to
                                                  //multiply by the normalized signal
    
    
    uint8_t resample_signals();
    uint8_t trimFile(); //TODO
    uint8_t multiplyWeight(); //TODO
    long    gcd(long a, long b);
    void    resize_filedata(std::vector<Col<double>> & newData);

public:
    mat filedata;    //raw samples

    wav2sig();
    wav2sig(std::vector<std::string> fnames_);
    wav2sig(std::vector<std::string> fnames_, int fs_);
    wav2sig(std::vector<std::string> fnames_, std::vector<float> tInt_);
    wav2sig(std::vector<std::string> fnames_, std::vector<double> weights_);
    wav2sig(std::vector<std::string> fnames_, int fs_, std::vector<float> tInt_);
    wav2sig(std::vector<std::string> fnames_, int fs_, std::vector<double> weights_);
    wav2sig(std::vector<std::string> fnames_, std::vector<float> tInt_,std::vector<double> weights_);
    wav2sig(std::vector<std::string> fnames_,
            int fs_,
            std::vector<float> tInt_,
            std::vector<double> weights_);

    void read();
    void write();
    std::vector<std::string> get_fnames() { return fnames; };
    uint8_t get_num_files() {return num_files; };
    std::vector<int> get_channel_fs() {return channel_fs; };
};

#endif