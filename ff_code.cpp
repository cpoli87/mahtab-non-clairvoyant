#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <random>
#include <cassert>
#include <cstdlib>
#include <string>
#include <thread>
#include <tuple>
#include <utility>
using namespace std;


// class Job {
// public:
//     int start, end, size;

//     Job(int _start, int _end, int _size) : start(_start), end(_end), size(_size) {}
// };

class Job_dimensional{
public:    
    int start, end;
    std::vector<int> size;

    Job_dimensional(int _start, int _end, const std:: vector<int>& _size): start(_start), end(_end), size(_size){}

};


// bool job_compare(Job & j1, Job & j2) {
//     return j1.start < j2.start;
// }

bool compareJobs(const Job_dimensional& a, const Job_dimensional& b) {
    return a.start < b.start;
}

// void print_jobs(vector<Job> & jobs) {
//     for(int i = 0; i < jobs.size(); i++)
//         cout << "Job #" << (i+1) << " start: " << jobs[i].start << " end: " << jobs[i].end << " size: " << jobs[i].size << endl;
// }

void print_jobs_dimensional(const vector<Job_dimensional>& jobs) {
    for (int i = 0; i < jobs.size(); i++) {
        cout << "Job #" << (i + 1) << " start: " << jobs[i].start << " end: " << jobs[i].end << " size: ";

        // Print each element of the size vector
        for (int j = 0; j < jobs[i].size.size(); j++) {
            cout << jobs[i].size[j];
            if (j < jobs[i].size.size() - 1) {
                cout << ", ";  // Print comma between elements
            }
        }

        cout << endl;
    }
}

// vector<Job> generate_jobs_on_interval(int T, int mu, int E, int n) {
//     vector<Job> res;
//     random_device rand_dev;
//     mt19937 generator(rand_dev());
//     uniform_int_distribution<int> time_dist(1, T-mu);
//     uniform_int_distribution<int> size_dist(1, E);
//     uniform_int_distribution<int> length_dist(1, mu);
//     vector<int> arrivals(n, 0);
//     for(int i = 0; i < n; i++) {
//         arrivals[i] = time_dist(generator);
        
//     }
//     sort(arrivals.begin(), arrivals.end());
//     for(int i = 0; i < n; i++) {
//         res.push_back(Job(arrivals[i], arrivals[i] + length_dist(generator), size_dist(generator)));
//     }
//     return res;
// }

std::vector<Job_dimensional> generate_dimensional_jobs_on_interval(int T, int mu, const std::vector<int>& E, int n){
    vector<Job_dimensional> res;
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> time_dist(1, T-mu);
    uniform_int_distribution<int> length_dist(1, mu);
    for (int i = 0; i < n; i++) {
        int arrival_time = time_dist(generator);
        int end_time = arrival_time + length_dist(generator);

        std::vector<int> job_sizes;
        for (int j = 0; j < E.size(); j++) {
            std::uniform_int_distribution<int> size_dist(1, E[j]);
            job_sizes.push_back(size_dist(generator));
        }
        
        res.push_back(Job_dimensional(arrival_time, end_time, job_sizes));
    }

    // Sorting based on arrival time
    // std::sort(res.begin(), res.end(), [](const Job_dimensional& a, const Job_dimensional& b) {
    //     return a.start < b.start;
    // });
    std::sort(res.begin(), res.end(), compareJobs);

    return res;

}


// long long volume(vector<Job> & jobs) {
//     long long ans = 0;
//     for(int i = 0; i < jobs.size(); i++) {
//         ans += (long long)(jobs[i].end - jobs[i].start)*((long long)jobs[i].size);
//     }
//     return ans;
// }



//std::vector<long long> volume_dimensional(vector<Job_dimensional> & jobs) {
long long volume_dimensional(vector<Job_dimensional> & jobs) {    
    size_t dimensions = jobs.empty() ? 0 : jobs.front().size.size();
    std::vector<long long> ans(dimensions, 0);

    for (const auto& job : jobs) {
        for (size_t i = 0; i < dimensions; ++i) {
            ans[i] += static_cast<long long>(job.end - job.start) * static_cast<long long>(job.size[i]);
        }
    }

    long long maxVolume = *std::max_element(ans.begin(), ans.end());

    return maxVolume;
}

// class Opt {
// private:
//     std::vector<Job> jobs;

// public:
//     Opt(const std::vector<Job>& list_of_intervals) : jobs(list_of_intervals) {}

//     int volumeAtTime(int time) {
//         int result = 0;
//         for (const Job& job : jobs) {
//             if (time >= job.start && time < job.end) {
//                 result += job.size;
//             }
//         }
//         return result;
//     }



// //     int computeWaste(const std::vector<Job>& jobs) {
// //     std::vector<int> xs;
// //     for (const Job& job : jobs) {
// //         xs.push_back(job.size); 
// //     }
// //     std::sort(xs.begin(), xs.end(), std::greater<int>());

// //     int carry = 0;
// //     int waste = 0;

// //     while (!xs.empty()) {
// //         int j = xs.size() - 1;
// //         while (j > 0) {
// //             if (xs[j] <= E - xs[0]) {
// //                 carry += xs[j];
// //             } else {
// //                 break;
// //             }
// //             j--;
// //         }

// //         if (carry + xs[0] <= E) {
// //             waste += E - xs[0] - carry;
// //             carry = 0;
// //         } else {
// //             carry -= E - xs[0];
// //         }

// //         xs.erase(xs.begin(), xs.begin() + j + 1);
// //     }

// //     carry -= carry / E * E;
// //     if (carry > 0) {
// //         waste += E - carry;
// //     }

// //     return waste;
// // }


//     // long long newLB(int E) {
//     // long long newLB = 0LL;
//     // std::vector<int> eventTimes;
    
//     // for (const Job& job : jobs) {
//     //     eventTimes.push_back(job.start);
//     //     eventTimes.push_back(job.end);
//     // }
    
//     // std::sort(eventTimes.begin(), eventTimes.end());
    
//     // for (size_t i = 0; i < eventTimes.size() - 1; i++) {
//     //     int duration = eventTimes[i + 1] - eventTimes[i];
//     //     int volume = volumeAtTime(eventTimes[i]);
//     //     //double waste = computeWaste(jobs[eventTimes[i]]);
//     //     std::vector<Job> jobsForInterval;
//     //     for (const Job& job : jobs) {
//     //         if (job.start <= eventTimes[i] && job.end > eventTimes[i]) {
//     //            jobsForInterval.push_back(job);
//     //            }
//     //     }
//     //     double waste = computeWaste(jobsForInterval);
        
//     //     newLB += static_cast<long long>(duration) * (volume + waste);
//     // }
//     // return newLB;

//     // }
// // 


//    std::pair<long long, long long> ceilLBandSpan( int E) {
//     long long ceilLB = 0LL;
//     long long span = 0LL;
//     std::vector<int> eventTimes;

//     for (const Job& job : jobs) {
//         eventTimes.push_back(job.start);
//         eventTimes.push_back(job.end);
//     }

//     std::sort(eventTimes.begin(), eventTimes.end());

//     for (size_t i = 0; i < eventTimes.size() - 1; i++) {
//         int duration = eventTimes[i + 1] - eventTimes[i];
//         int volume = volumeAtTime(eventTimes[i]);

//         span += static_cast<long long>(duration);
        
//         if (volume % E != 0) {
//             volume = ((volume / E) + 1) * E;
//         } else {
//             volume = volume;
//         }
            
//         ceilLB += static_cast<long long>(duration) * volume;
//     }
//     return std::make_pair(ceilLB, span);
//     }
// };

class Opt_dimensional {
private:
    std::vector<Job_dimensional> jobs;

public:
    Opt_dimensional(const std::vector<Job_dimensional>& list_of_intervals) : jobs(list_of_intervals) {}

    std::vector<int> volumeAtTime(int time) {
        std::vector<int> result(jobs[0].size.size(), 0);//initialize the result vector with 0 at each element

        for (const Job_dimensional& job : jobs) {
            if (time >= job.start && time < job.end) {
                for (size_t i = 0; i < job.size.size(); ++i) {
                    result[i] += job.size[i];
                }
            }
        }

        return result;
    }

    std::pair<long long, long long> ceilLBandSpan(const std::vector<int>& E) {
        long long ceilLB = 0LL;
        long long span = 0LL;
        std::vector<int> eventTimes;

        for (const Job_dimensional& job : jobs) {
            eventTimes.push_back(job.start);
            eventTimes.push_back(job.end);
        }

        std::sort(eventTimes.begin(), eventTimes.end());

        for (size_t i = 0; i < eventTimes.size() - 1; i++) {
            int duration = eventTimes[i + 1] - eventTimes[i];
            std::vector<int> volume = volumeAtTime(eventTimes[i]);

            span += static_cast<long long>(duration); // Increment span separately, if needed

            // Rounding logic
            for (size_t j = 0; j < volume.size(); ++j) {
                int currentE = E[j];
                if (volume[j] % currentE != 0) {
                    volume[j] = ((volume[j] / currentE) + 1) * currentE;
                } else {
                    volume[j] = volume[j];
                }
            }
            // Find the maximum value in the rounded volume vector
            int maxVolume = *std::max_element(volume.begin(), volume.end());

            // Use the maximum value in the calculation
            ceilLB += static_cast<long long>(duration) * maxVolume;  
        }
        return std::make_pair(ceilLB, span);
    }
};





// class Server {
// public:
//     int capacity;
//     int start_time;
//     int cur_time;
//     int finish_time; // -1 if server is still active, and set to finish time if server is not active
//     bool is_active;
//     int cur_size; // total size of all jobs alive at time cur_time if the server is active, 0 otherwise
//     map<int, int> cur_jobs; // jobs with start time < cur_time and finish time > cur_time, represented by (finish_time, size), must be sorted by

//     // Start a new server with a given job
//     Server(Job &firstJob, int _capacity) {
//         assert(firstJob.size <= _capacity);
//         capacity = _capacity;
//         start_time = cur_time = firstJob.start;
//         finish_time = -1;
//         //finish_time = firstJob.end;
//         is_active = true;
//         cur_size = firstJob.size;
//         cur_jobs[firstJob.end] = firstJob.size;
//     }

//     // advance time from cur_time to to_time
//     // return true if the server has not finished yet, otherwise return false
//     bool advance_time(int to_time) {
//         if(to_time >= cur_time) {
//             cur_time = to_time;
//             if(!is_active) {
//                 return false;
//             } else {
//                 assert(cur_jobs.size() > 0);
//                 typeof(cur_jobs.begin()) it = cur_jobs.begin();

//                 while(it != cur_jobs.end() && it->first < to_time) {
//                     cur_size -= it->second;
//                     it++;
//                 }
//                 if(it == cur_jobs.end()) {
//                     deactivate();
//                     //finish_time = cur_jobs.rbegin()->first;
//                     //is_active = false;
//                 }
//                 cur_jobs.erase(cur_jobs.begin(), it);
//                 return is_active;
//             }
//         }
//         return false;
//     }

//     // Tries to add a given job to a server:
//     //   start by advancing time to the beginning of the job
//     //     if a server is active and has enough capacity, add the job to the server
//     // Returns true if job was succesfully placed, and false otherwise
//     bool add_job(Job & j) {
//         if(advance_time(j.start)) {
//             if(cur_size + j.size <= capacity) {
//                 if(cur_jobs.find(j.end) != cur_jobs.end()) {
//                     cur_jobs[j.end] += j.size; // if there is already a job with given end-time, add this job size to it
//                 } else {
//                     cur_jobs[j.end] = j.size;
//                 }
//                 cur_size += j.size;
//                 //finish_time = j.end;
//                 return true;
//             }
//         }
//         return false;
//     }

//     // If the server is not active, return finish time minus start time
//     // Otherwise, return latest finish time of current jobs minus start time
//     int duration() {
//         if(!is_active) {
//             return finish_time-start_time;
//         } else {
//             assert(cur_jobs.size()>0);
//             return cur_jobs.rbegin()->first - start_time;
//         }
//     }

//     int remaining_capacity(){
//         return capacity - cur_size;
//     }

//     // make the server inactive
//     void deactivate() {
//         if(is_active) {
//             if(!cur_jobs.empty()) {
//                 finish_time = cur_jobs.rbegin()->first;
//             }
//             cur_size = 0;
//             cur_jobs.clear();
//             is_active = false;
//         }
//     }

//     int get_server_finishing_time() {
//     int latest_finish_time = -1;

//     if (is_active) {
//         for (const auto& job : cur_jobs) {
//             if (job.first > latest_finish_time) {
//                 latest_finish_time = job.first;
//             }
//         }
//     } else {
//         latest_finish_time = finish_time;
//     }

//     return latest_finish_time;
// }


//     void print_status() {
//         cout << "Capacity: " << capacity << " start time: " << start_time << " current time: " << cur_time
//              << " finish time: " << finish_time << " current size: " << cur_size
//              << " duration: " << duration() << endl;

//         cout << "Is active: " << is_active << endl;
//         cout << "Current jobs:" << endl;
//         for(typeof(cur_jobs.begin()) it = cur_jobs.begin(); it != cur_jobs.end(); it++) {
//             cout << "\tJob ending at " << it->first << " of size " << it->second << endl;
//         }
//     }

// };


class Server_dimensional{
    public:
    std::vector<int> capacity;
    int start_time;
    int cur_time;
    //std::vector<int> finish_time; // -1 if server is still active, and set to finish time if server is not active
    int finish_time;
    bool is_active;
    std::vector<int> cur_size; // each element is the total size of all jobs(at that dimension) alive at time cur_time if the server is active, 0 otherwise
    std::map<int, std::vector<int> > cur_jobs; // jobs with start time < cur_time and finish time > cur_time, represented by (finish_time, size), must be sorted by

    // Start a new server with a given job
    Server_dimensional(Job_dimensional &firstJob, std::vector<int> &_capacity) {
        assert(firstJob.size.size() == _capacity.size());
        for (size_t i = 0; i < firstJob.size.size(); ++i) {
            assert(firstJob.size[i] <= _capacity[i]);
        }

        capacity = _capacity;
        start_time = cur_time = firstJob.start;
        //finish_time = std::vector<int>(capacity.size(), -1); // Initialize all finish_time values to -1
        finish_time = -1;
        is_active = true;
        cur_size = std::vector<int>(capacity.size(), 0); // Initialize all cur_size values to 0
        cur_jobs[firstJob.end] = firstJob.size;

        // Copy the elements of firstJob.size into cur_size element by element
        for (size_t i = 0; i < firstJob.size.size(); ++i) {
            cur_size[i] = firstJob.size[i];
        }
    }

    bool advance_time(int to_time) {
        if (to_time >= cur_time) {
            cur_time = to_time;
            if (!is_active) {
                return false;
            } else
             {
                assert(cur_jobs.size() > 0);
                auto it = cur_jobs.begin();
                while (it != cur_jobs.end() && it->first < to_time) {
                    const std::vector<int>& jobSizeVector = it->second;
                    // Update cur_size element-wise
                    for (size_t i = 0; i < cur_size.size(); ++i) {
                        cur_size[i] -= jobSizeVector[i];
                    }
                    it++;
                }

                if (it == cur_jobs.end()) {
                    deactivate();
                }

                // Erase elements from cur_jobs
                cur_jobs.erase(cur_jobs.begin(), it);
                return is_active;
            }
        }
        return false;
    } 
    
     bool add_job(Job_dimensional &j) {
        if (advance_time(j.start)) {
            bool hasEnoughCapacity = true;
            for (size_t i = 0; i < j.size.size(); ++i) {
                if (cur_size[i] + j.size[i] > capacity[i]) {
                    hasEnoughCapacity = false;
                    break;
                }
            }

            if (hasEnoughCapacity) {
                if (cur_jobs.find(j.end) != cur_jobs.end()) {
                    // if there is already a job with the given end-time, add this job size to it
                    for (size_t i = 0; i < j.size.size(); ++i) {
                        cur_jobs[j.end][i] += j.size[i];
                }
                } else {
                    cur_jobs[j.end] = j.size;
                }

                // Update cur_size element-wise
                for (size_t i = 0; i < cur_size.size(); ++i) {
                    cur_size[i] += j.size[i];
                }

                // finish_time = j.end; // Uncomment if needed
                return true;
            }
        }

        return false;
    }

    // If the server is not active, return finish time minus start time
    // Otherwise, return latest finish time of current jobs minus start time
    int duration() {
        if(!is_active) {
            return finish_time-start_time;
        } else {
            assert(cur_jobs.size()>0);
            return cur_jobs.rbegin()->first - start_time;
        }
    } 


    std::vector<int> remaining_capacity(){
        std::vector<int> remainingCapacity(capacity.size());

        for (size_t i = 0; i< capacity.size(); i++){
            remainingCapacity[i] = capacity[i] - cur_size[i];
        }
        return remainingCapacity;

    }



    void deactivate() {
        if(is_active) {
            if(!cur_jobs.empty()) {
                finish_time = cur_jobs.rbegin()->first;
            }

            for (size_t i=0; i< cur_size.size(); i++ ){
                cur_size[i] == 0;
            }
            cur_jobs.clear();
            is_active = false;
        }
    }

    int get_server_finishing_time() {
        int latest_finish_time = -1;
        if (is_active) {
            for (const auto& job : cur_jobs) {
                if (job.first > latest_finish_time) {
                    latest_finish_time = job.first;
                }
            }
        } else {
            latest_finish_time = finish_time;
        }

        return latest_finish_time;
    }

    void print_status() {
        cout << "Capacity: ";
        for (size_t i = 0; i < capacity.size(); ++i) {
            cout << capacity[i] << " ";
        }

        cout << "start time: " << start_time << " current time: " << cur_time
             << " finish time: " << finish_time;

        cout << " current size: ";
        for (size_t i = 0; i < cur_size.size(); ++i) {
            cout << cur_size[i] << " ";
        }

        cout << " duration: " << duration() << endl;

        cout << "Is active: " << is_active << endl;

        cout << "Current jobs:" << endl;
        for (const auto& entry : cur_jobs) {
            cout << "\tJob ending at " << entry.first << " of size: ";
            for (size_t i = 0; i < entry.second.size(); ++i) {
                cout << entry.second[i] << " ";
            }
            cout << endl;
        }
    }

};


// class FirstFit {
// public:
//     vector<Server> all_servers;
//     vector<int> active_servers_idx;
//     int cur_time;
//     int capacity;

//     FirstFit(int _capacity): cur_time(0), capacity(_capacity) {}


//     void add_job(Job &j) {
//         assert(j.start >= cur_time); // jobs should be added by non-decreasing start times
//         cur_time = j.start;

//         bool placed = false;
//         typeof(active_servers_idx.begin()) it = active_servers_idx.begin();
//         while(it != active_servers_idx.end() && !placed) {
//             // try placing job in the current server
//             placed = all_servers[*it].add_job(j);
//             if(!placed) {
//                 // check if a server is still active
//                 if(all_servers[*it].is_active) {
//                     it++;
//                 } else {
//                     it = active_servers_idx.erase(it);
//                 }
//             }
//         }
//         // If not placed, create a new server
//         if (!placed) {
//             all_servers.push_back(Server(j, capacity));
//             active_servers_idx.push_back((int) all_servers.size()-1);
//         }
//     }

//     void print_servers() {
//         cout << "------------------FIRST FIT STATUS BEGIN ----------------------" << endl;
//         int server_num = 1;
//         for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
//             cout << "*** status of server " << server_num << " ***" << endl;
//             server_num++;
//             (*it).print_status();
//         }
//         cout << "------------------FIRST FIT STATUS END ------------------------" << endl;
//     }

//     long long cost() {
//         long long res = 0;
//         for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
//             res += (*it).duration();
//         }
//         return res;
//     }
// };


class FirstFit_dimensional {
public:
    vector<Server_dimensional> all_servers;
    vector<int> active_servers_idx;
    int cur_time;
    std::vector<int> capacity;

    FirstFit_dimensional(const std::vector<int>& _capacity): cur_time(0), capacity(_capacity) {}


    void add_job(Job_dimensional &j) {
        assert(j.start >= cur_time); // jobs should be added by non-decreasing start times
        cur_time = j.start;

        bool placed = false;
        typeof(active_servers_idx.begin()) it = active_servers_idx.begin();
        while(it != active_servers_idx.end() && !placed) {
            // try placing job in the current server
            placed = all_servers[*it].add_job(j);
            if(!placed) {
                // check if a server is still active
                if(all_servers[*it].is_active) {
                    it++;
                } else {
                    it = active_servers_idx.erase(it);
                }
            }
        }
        // If not placed, create a new server
        if (!placed) {
            all_servers.push_back(Server_dimensional(j, capacity));
            active_servers_idx.push_back(static_cast<int> (all_servers.size())-1);
        }
    }

    void print_servers() {
        cout << "------------------FIRST FIT STATUS BEGIN ----------------------" << endl;
        int server_num = 1;
        for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
            cout << "*** status of server " << server_num << " ***" << endl;
            server_num++;
            (*it).print_status();
        }
        cout << "------------------FIRST FIT STATUS END ------------------------" << endl;
    }

    long long cost() {
        long long res = 0;
        for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
            res += (*it).duration();
        }
        return res;
    }

    void add_job_active(Job_dimensional &j)
    {
        assert(j.start >= cur_time); // jobs should be added by non-decreasing start times
        cur_time = j.start;

        bool placed = false;
        typeof(active_servers_idx.begin()) it = active_servers_idx.begin();
        bool hasActiveServer = false;

        for (int idx : active_servers_idx)
        {
            if (all_servers[idx].is_active)
            {
                hasActiveServer = true;
                break; // No need to continue checking once we find an active server
            }
        }

        if (hasActiveServer)
        {
            add_job(j);
        }
    }
};


// class ModifiedFirstFit {
// public:
//     FirstFit ffSmall, ffLarge;
//     int capacity;
//     int threshold; // small jobs are those that are <= threshold

//     ModifiedFirstFit(int _capacity, int _threshold): capacity(_capacity), threshold(_threshold), ffSmall(_capacity), ffLarge(_capacity) {}

//     void add_job(Job &j) {
//         if (j.size < threshold) {
//             ffSmall.add_job(j);
//         } else {
//             ffLarge.add_job(j);
//         }
//     }

//     void print_servers() {
//         cout << "************** SMALL JOB SERVERS ******************"<<endl;
//         ffSmall.print_servers();
//         cout << "************** LARGE JOB SERVERS ******************"<<endl;
//         ffLarge.print_servers();
//     }

//     long long cost() {
//         return ffSmall.cost() + ffLarge.cost();
//     }
// };

class ModifiedFirstFit_dimensional {
public:
    FirstFit_dimensional ffSmall, ffLarge;
    std::vector<int> capacity;
    int threshold; // small jobs are those that are <= threshold

    ModifiedFirstFit_dimensional(const std::vector<int>& _capacity, int _threshold): capacity(_capacity), threshold(_threshold), ffSmall(_capacity), ffLarge(_capacity) {}

    void add_job(Job_dimensional &j) {
        bool isSmallJob = true;

        for (size_t i = 0; i < j.size.size(); ++i) {
            if (j.size[i] >= threshold) {
                isSmallJob = false;
                break;
            }
        }
        if (isSmallJob) {
            ffSmall.add_job(j);
        } else {
            ffLarge.add_job(j);
        }
    }

    void print_servers() {
        cout << "************** SMALL JOB SERVERS ******************"<<endl;
        ffSmall.print_servers();
        cout << "************** LARGE JOB SERVERS ******************"<<endl;
        ffLarge.print_servers();
    }

    long long cost() {
        return ffSmall.cost() + ffLarge.cost();
    }
};

// class MTF {
// public:
//     vector<Server> all_servers;
//     vector<int> active_servers_idx;
//     int cur_time;
//     int capacity;

//     MTF(int _capacity): cur_time(0), capacity(_capacity) {}

//     void add_job(Job& j) {
//         assert(j.start >= cur_time); // jobs should be added by non-decreasing start times
//         cur_time = j.start;

//         bool placed = false;
//         auto it = active_servers_idx.begin();
//         while (it != active_servers_idx.end() && !placed) {
//             int serverIdx = *it;
//             if (all_servers[serverIdx].is_active) {
//                 placed = all_servers[serverIdx].add_job(j);
//                 if (placed) {
//                     // Move the assigned server to the front of the list
//                     active_servers_idx.erase(it);
//                     active_servers_idx.insert(active_servers_idx.begin(), serverIdx);
//                 }
//             }
//             if (!placed) {
//                 if (!all_servers[serverIdx].is_active) {
//                     it = active_servers_idx.erase(it);
//                 } else {
//                     ++it;
//                 }
//             }
//         }

//         if (!placed) {
//             // Create a new server
//             all_servers.push_back(Server(j, capacity));
//             int newIndex = static_cast<int>(all_servers.size()) - 1;
//             active_servers_idx.insert(active_servers_idx.begin(), newIndex);
//         }
//     }


//     void print_servers() {
//         cout << "------------------MTF STATUS BEGIN ----------------------" << endl;
//         int server_num = 1;
//         for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
//             cout << "*** status of server " << server_num << " ***" << endl;
//             server_num++;
//             (*it).print_status();
//         }
//         cout << "------------------MTF STATUS END ------------------------" << endl;
//     }

//     long long cost() {
//         long long res = 0;
//         for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
//             res += (*it).duration();
//         }
//         return res;
//     }
// };

class MTF_dimensional {
public:
    vector<Server_dimensional> all_servers;
    vector<int> active_servers_idx;
    int cur_time;
    std::vector<int> capacity;

    MTF_dimensional(const std::vector<int>& _capacity): cur_time(0), capacity(_capacity) {}

    void add_job(Job_dimensional& j) {
        assert(j.start >= cur_time); // jobs should be added by non-decreasing start times
        cur_time = j.start;

        bool placed = false;
        auto it = active_servers_idx.begin();
        while (it != active_servers_idx.end() && !placed) {
            int serverIdx = *it;
            if (all_servers[serverIdx].is_active) {
                placed = all_servers[serverIdx].add_job(j);
                if (placed) {
                    // Move the assigned server to the front of the list
                    active_servers_idx.erase(it);
                    active_servers_idx.insert(active_servers_idx.begin(), serverIdx);
                }
            }
            if (!placed) {
                if (!all_servers[serverIdx].is_active) {
                    it = active_servers_idx.erase(it);
                } else {
                    ++it;
                }
            }
        }

        if (!placed) {
            // Create a new server
            all_servers.push_back(Server_dimensional(j, capacity));
            int newIndex = static_cast<int>(all_servers.size()) - 1;
            active_servers_idx.insert(active_servers_idx.begin(), newIndex);
        }
    }


    void print_servers() {
        cout << "------------------MTF STATUS BEGIN ----------------------" << endl;
        int server_num = 1;
        for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
            cout << "*** status of server " << server_num << " ***" << endl;
            server_num++;
            (*it).print_status();
        }
        cout << "------------------MTF STATUS END ------------------------" << endl;
    }

    long long cost() {
        long long res = 0;
        for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
            res += (*it).duration();
        }
        return res;
    }
};


// class New_MTF{
//     public:
//     vector<Server> all_servers;
//     vector<int> active_servers_idx;
//     int cur_time;
//     int capacity;

//     New_MTF(int _capacity): cur_time(0), capacity(_capacity) {}

//     void add_job(Job& j) {
//         assert(j.start >= cur_time); // jobs should be added by non-decreasing start times

//         // Advance time for BF and all its servers and update active_server_idx
//         cur_time = j.start;

//         auto it = active_servers_idx.begin();
//         while (it != active_servers_idx.end()) {
//             if (!all_servers[*it].advance_time(cur_time)) {
//                 it = active_servers_idx.erase(it);
//                 continue;
//             } else {
//                 ++it;
//             }
//         }

//         // Find a server (if it exists) that can accommodate the job and has best fit
//         int min_remain_capacity_idx = -1;
//         // Find the server with the minimum remaining capacity
//         it = active_servers_idx.begin();
//         while (it != active_servers_idx.end()) {
//             if(all_servers[*it].remaining_capacity() >= j.size &&
//             (min_remain_capacity_idx == -1 || all_servers[*it].remaining_capacity() < all_servers[min_remain_capacity_idx].remaining_capacity())) {
//                 min_remain_capacity_idx = *it;
//             }
//             ++it;
//         }

//         if (min_remain_capacity_idx != -1) {
//             all_servers[min_remain_capacity_idx].add_job(j);

//             // Move the assigned server to the front of the list
//             active_servers_idx.erase(remove(active_servers_idx.begin(), active_servers_idx.end(), min_remain_capacity_idx), active_servers_idx.end());
//             active_servers_idx.insert(active_servers_idx.begin(), min_remain_capacity_idx);
//         } else {
//             // If no active server has enough capacity, create a new server and bring it to the front
//             all_servers.push_back(Server(j, capacity));
//             int newIndex = static_cast<int>(all_servers.size()) - 1;
//             active_servers_idx.insert(active_servers_idx.begin(), newIndex);
//         }
//     }

//       void print_servers() {
//         cout << "------------------MTF STATUS BEGIN ----------------------" << endl;
//         int server_num = 1;
//         for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
//             cout << "*** status of server " << server_num << " ***" << endl;
//             server_num++;
//             (*it).print_status();
//         }
//         cout << "------------------MTF STATUS END ------------------------" << endl;
//     }

//     long long cost() {
//         long long res = 0;
//         for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
//             res += (*it).duration();
//         }
//         return res;
//     }   

// };


// class BIT{
//     public:
//         vector<Server> all_servers;
//         vector<int> active_servers_idx;
//         vector<int> active_servers_bit;
//         int cur_time;
//         int capacity;


//         BIT(int _capacity): cur_time(0), capacity(_capacity){}

//         void add_job(Job &j){
//             assert(j.start >= cur_time); //jobs should be added by non-decreasing start time
//             cur_time = j.start;
//             double p = 0.1;

//             bool placed = false;
//             auto it = active_servers_idx.begin();
//             while (it != active_servers_idx.end() && !placed){
//                 int serverIdx = *it;
//                 if (all_servers[serverIdx].is_active){
//                     placed = all_servers[serverIdx].add_job(j);
//                     if (placed){
//                         if (active_servers_bit[serverIdx] == 1){
//                             active_servers_idx.erase(it);
//                             active_servers_idx.insert(active_servers_idx.begin(), serverIdx);
//                             active_servers_bit[serverIdx] =  active_servers_bit[serverIdx] - 1;
//                         }
//                     }
//                 }
//                 if (!placed) {
//                     if (!all_servers[serverIdx].is_active) {
//                         it = active_servers_idx.erase(it);
//                     }
//                     else {
//                         ++it;
//                     }
//                 }
//             }
//             if (!placed){
//                 //create a new server 

//                 //std::srand(static_cast<unsigned int>(std::time(0)));//  create a random bit 
//                 all_servers.push_back(Server(j, capacity));
//                 active_servers_idx.push_back((int) all_servers.size()-1);
//                 // int randomBit = rand() % 2;
//                 // active_servers_bit.push_back(randomBit);
//                 std::random_device rd;
//                 std::mt19937 rng(rd());
//                 std::uniform_real_distribution<double> dist(0.0, 1.0);
//                 double randomValue = dist(rng);
//                 // Decide whether to set the bit to 0 or 1 based on the probability p
//                 int randomBit = (randomValue < p) ? 0 : 1;
//                 active_servers_bit.push_back(randomBit);
//             }
//         }

            

//         void print_servers() {
//             cout << "------------------MTF STATUS BEGIN ----------------------" << endl;
//             int server_num = 1;
//             for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
//                 cout << "*** status of server " << server_num << " ***" << endl;
//                 server_num++;
//                 (*it).print_status();
//             }
//             cout << "------------------MTF STATUS END ------------------------" << endl;
//         }

//         long long cost() {
//             long long res = 0;
//             for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
//                 res += (*it).duration();
//             }
//             return res;
//         }  

// };


// class BestFit {
// public:
//     vector<Server> all_servers;
//     vector<int> active_servers_idx;
//     int cur_time;
//     int capacity;

//     BestFit(int _capacity) : cur_time(0), capacity(_capacity) {}

//     void add_job(Job& j) {
//         assert(j.start >= cur_time); // Jobs should be added by non-decreasing start times

//         // Advance time for BF and all its servers and update active_server_idx
//         cur_time = j.start;

//         auto it = active_servers_idx.begin();
//         while (it != active_servers_idx.end()) {
//             if (!all_servers[*it].advance_time(cur_time)) {
//                 it = active_servers_idx.erase(it);
//                 continue;
//             } else {
//                 ++it;
//             }
//         }

//         // Find a server (if it exist) that can accommodate the job and has best fit
//         int min_remain_capacity_idx = -1;
//         // Find the server with the minimum remaining capacity
//         it = active_servers_idx.begin();
//         while (it != active_servers_idx.end()) {
//             if(all_servers[*it].remaining_capacity() >= j.size &&
//             (min_remain_capacity_idx == -1 || all_servers[*it].remaining_capacity() < all_servers[min_remain_capacity_idx].remaining_capacity())) {
//                 min_remain_capacity_idx = *it;
//             }
//             ++it;
//         }

//         if (min_remain_capacity_idx != -1) {
//             all_servers[min_remain_capacity_idx].add_job(j);
//         } else {

//             // If no active server has enough capacity, create a new server
//             all_servers.push_back(Server(j, capacity));
//             int newIndex = static_cast<int>(all_servers.size()) - 1;
//             active_servers_idx.push_back(newIndex);
//         }

//     }

//     void print_servers() {
//         cout << "------------------Best FIT STATUS BEGIN ----------------------" << endl;
//         int server_num = 1;
//         for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
//             cout << "*** status of server " << server_num << " ***" << endl;
//             server_num++;
//             (*it).print_status();
//         }
//         cout << "------------------Best FIT STATUS END ------------------------" << endl;
//     }

//     long long cost() {
//         long long res = 0;
//         for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
//             res += (*it).duration();
//         }
//         return res;
//     }
// };

class BestFit_dimensional {
public:
    vector<Server_dimensional> all_servers;
    vector<int> active_servers_idx;
    int cur_time;
    std::vector<int> capacity;


    BestFit_dimensional(const std::vector<int>& _capacity) : cur_time(0), capacity(_capacity) {}

    void add_job(Job_dimensional& j) {
        assert(j.start >= cur_time); // Jobs should be added by non-decreasing start times

        // Advance time for BF and all its servers and update active_server_idx
        cur_time = j.start;

        auto it = active_servers_idx.begin();
        while (it != active_servers_idx.end()) {
            if (!all_servers[*it].advance_time(cur_time)) {
                it = active_servers_idx.erase(it);
                continue;
            } else {
                ++it;
            }
        }

        // Find a server (if it exists) that can accommodate the job and has the best fit
        int min_remain_capacity_idx = -1;
        // Find the server with the minimum remaining capacity
        it = active_servers_idx.begin();
        while (it != active_servers_idx.end()) {
            bool enoughCapacity = true;
            std::vector<int> remaining_capacity = all_servers[*it].remaining_capacity();

            for (size_t i = 0; i < j.size.size(); ++i) {
                if (remaining_capacity[i] < j.size[i]) {
                    enoughCapacity = false;
                    break;
                }
            }

            if (enoughCapacity) {
                if (min_remain_capacity_idx == -1 || remaining_capacity < all_servers[min_remain_capacity_idx].remaining_capacity()) {
                    min_remain_capacity_idx = *it;
                }
            }
            ++it;
        }

        if (min_remain_capacity_idx != -1) {
            all_servers[min_remain_capacity_idx].add_job(j);
        } else {

            // If no active server has enough capacity, create a new server
            Server_dimensional new_server(j, capacity);
            all_servers.push_back(new_server);
            int newIndex = static_cast<int>(all_servers.size()) - 1;
            active_servers_idx.push_back(newIndex);
        }
    }

    void print_servers() {
        cout << "------------------Best FIT STATUS BEGIN ----------------------" << endl;
        int server_num = 1;
        for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
            cout << "*** status of server " << server_num << " ***" << endl;
            server_num++;
            (*it).print_status();
        }
        cout << "------------------Best FIT STATUS END ------------------------" << endl;
    }

    long long cost() {
        long long res = 0;
        for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
            res += (*it).duration();
        }
        return res;
    }
};

// class NextFit {
// public:
//     vector<Server> all_servers;
//     int cur_time;
//     int capacity;

//     NextFit(int _capacity) : cur_time(0), capacity(_capacity) {}

//     void add_job(Job &j) {
//         assert(j.start >= cur_time); // Jobs should be added by non-decreasing start times
//         cur_time = j.start;
//         if (all_servers.empty()) {
//             all_servers.push_back(Server(j, capacity));
//         } else {
//             if (!all_servers.rbegin()[0].add_job(j)) {
//                 // The job does not fit in the current open server
//                 all_servers.rbegin()[0].deactivate();
//                 all_servers.push_back(Server(j, capacity));
//             }
//         }
//     }

//     void print_servers() {
//         cout << "------------------Next FIT STATUS BEGIN ----------------------" << endl;
//         int server_num = 1;
//         for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
//             cout << "*** status of server " << server_num << " ***" << endl;
//             server_num++;
//             (*it).print_status();
//         }
//         cout << "------------------Next FIT STATUS END ------------------------" << endl;
//     }

//     long long cost() {
//         long long res = 0;
//         for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
//             res += (*it).duration();
//         }
//         return res;
//     }
// };

class NextFit_dimensional {
public:
    vector<Server_dimensional> all_servers;
    int cur_time;
    std::vector<int> capacity;

    NextFit_dimensional(const std::vector<int>& _capacity) : cur_time(0), capacity(_capacity) {}

    void add_job(Job_dimensional &j) {
        assert(j.start >= cur_time); // Jobs should be added by non-decreasing start times
        cur_time = j.start;
        if (all_servers.empty()) {
            all_servers.push_back(Server_dimensional(j, capacity));
        } else {
            if (!all_servers.rbegin()[0].add_job(j)) {
                // The job does not fit in the current open server
                all_servers.rbegin()[0].deactivate();
                all_servers.push_back(Server_dimensional(j, capacity));
            }
        }
    }

    void print_servers() {
        cout << "------------------Next FIT STATUS BEGIN ----------------------" << endl;
        int server_num = 1;
        for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
            cout << "*** status of server " << server_num << " ***" << endl;
            server_num++;
            (*it).print_status();
        }
        cout << "------------------Next FIT STATUS END ------------------------" << endl;
    }

    long long cost() {
        long long res = 0;
        for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
            res += (*it).duration();
        }
        return res;
    }
};

class ModifiedNextFit_dimensional {
public:
    NextFit_dimensional nfSmall, nfLarge;
    std::vector<int> capacity;
    int threshold; // small jobs are those that are <= threshold

    ModifiedNextFit_dimensional(const std::vector<int>& _capacity, int _threshold): capacity(_capacity), threshold(_threshold), nfSmall(_capacity), nfLarge(_capacity) {}

    void add_job(Job_dimensional &j) {
        bool isSmallJob = true;
        for (size_t i = 0; i < j.size.size(); ++i) {
            if (j.size[i] >= threshold) {
                isSmallJob = false;
                break;
            }
        }

        if (isSmallJob) {
            nfSmall.add_job(j);
        } else {
            nfLarge.add_job(j);
        }
    }

    void print_servers() {
        cout << "************** SMALL JOB SERVERS ******************"<<endl;
        nfSmall.print_servers();
        cout << "************** LARGE JOB SERVERS ******************"<<endl;
        nfLarge.print_servers();
    }

    long long cost() {
        return nfSmall.cost() + nfLarge.cost();
    }
};

// class ModifiedNextFit {
// public:
//     NextFit nfSmall, nfLarge;
//     int capacity;
//     int threshold; // small jobs are those that are <= threshold

//     ModifiedNextFit(int _capacity, int _threshold): capacity(_capacity), threshold(_threshold), nfSmall(_capacity), nfLarge(_capacity) {}

//     void add_job(Job &j) {
//         if (j.size < threshold) {
//             nfSmall.add_job(j);
//         } else {
//             nfLarge.add_job(j);
//         }
//     }

//     void print_servers() {
//         cout << "************** SMALL JOB SERVERS ******************"<<endl;
//         nfSmall.print_servers();
//         cout << "************** LARGE JOB SERVERS ******************"<<endl;
//         nfLarge.print_servers();
//     }

//     long long cost() {
//         return nfSmall.cost() + nfLarge.cost();
//     }
// };

// class HarmonicFit{
//     public:
//     NextFit nfinterval1, nfinterval2, nfinterval3, nfinterval4, nfinterval5, nfinterval6, nfinterval7, nfinterval8, nfinterval9, nfinterval10;
//     int capacity;
//     int interval_num;

// HarmonicFit(int _capacity, int _interval_num): capacity(_capacity), interval_num(_interval_num), nfinterval1(_capacity),  nfinterval2(_capacity),  nfinterval3(_capacity),  nfinterval4(_capacity),  nfinterval5(_capacity),  nfinterval6(_capacity),  nfinterval7(_capacity),  nfinterval8(_capacity),  nfinterval9(_capacity),  nfinterval10(_capacity){}

// void add_job(Job &j, int E) {
//     if (j.size <= (E / interval_num)) {
//         nfinterval1.add_job(j);
//     } else if ((E / interval_num) < j.size && j.size <= (E / (interval_num - 1))) {
//         nfinterval2.add_job(j);
//     } else if ((E / (interval_num - 1)) < j.size && j.size <= (E / (interval_num - 2))) {
//         nfinterval3.add_job(j);
//     } else if ((E / (interval_num - 2)) < j.size && j.size <= (E / (interval_num - 3))) {
//         nfinterval4.add_job(j);
//     } else if ((E / (interval_num - 3)) < j.size && j.size <= (E / (interval_num - 4))) {
//         nfinterval5.add_job(j);
//     } else if ((E / (interval_num - 4)) < j.size && j.size <= (E / (interval_num - 5))) {
//         nfinterval6.add_job(j);
//     } else if ((E / (interval_num - 5)) < j.size && j.size <= (E / (interval_num - 6))) {
//         nfinterval7.add_job(j);
//     } else if ((E / (interval_num - 6)) < j.size && j.size <= (E / (interval_num - 7))) {
//         nfinterval8.add_job(j);
//     } else if ((E / (interval_num - 7)) < j.size && j.size <= (E / (interval_num - 8))) {
//         nfinterval9.add_job(j);
//     } else if ((E / (interval_num - 8)) < j.size && j.size <= E) {
//         nfinterval10.add_job(j);
//     }
// }
//     void print_servers(){
//         cout << "************** First Interval Jobs ******************"<<endl;
//         nfinterval1.print_servers();
//         cout << "************** Second Interval Jobs ******************"<<endl;
//         nfinterval2.print_servers();
//         cout << "************** Third Interval Jobs ******************"<<endl;
//         nfinterval3.print_servers();
//         cout << "************** Forth Interval Jobs ******************"<<endl;
//         nfinterval4.print_servers();
//         cout << "************** Fifth Interval Jobs ******************"<<endl;
//         nfinterval5.print_servers();
//         cout << "************** Sixth Interval Jobs ******************"<<endl;
//         nfinterval6.print_servers();
//         cout << "************** Seventh Interval Jobs ******************"<<endl;
//         nfinterval7.print_servers();
//         cout << "************** eight Interval Jobs ******************"<<endl;
//         nfinterval8.print_servers();
//         cout << "************** nine Interval Jobs ******************"<<endl;
//         nfinterval9.print_servers();
//         cout << "************** ten Interval Jobs ******************"<<endl;
//         nfinterval10.print_servers();
//     }

//     long long cost(){
//         return nfinterval1.cost() + nfinterval2.cost()+ nfinterval3.cost()+ nfinterval4.cost()+nfinterval5.cost()+ nfinterval6.cost() + nfinterval7.cost()+ nfinterval8.cost()+ nfinterval9.cost()+ nfinterval10.cost();
//     }

// };

class HarmonicFit_dimensional{
    public:
    NextFit_dimensional nfinterval1, nfinterval2, nfinterval3, nfinterval4, nfinterval5, nfinterval6, nfinterval7, nfinterval8, nfinterval9, nfinterval10;
    std::vector<int> capacity;
    int interval_num;

HarmonicFit_dimensional(const std::vector<int>& _capacity, int _interval_num): capacity(_capacity), interval_num(_interval_num), nfinterval1(_capacity),  nfinterval2(_capacity),  nfinterval3(_capacity),  nfinterval4(_capacity),  nfinterval5(_capacity),  nfinterval6(_capacity),  nfinterval7(_capacity),  nfinterval8(_capacity),  nfinterval9(_capacity),  nfinterval10(_capacity){}

void add_job(Job_dimensional &j, const std::vector<int>& E) {
    for (size_t i = 0; i < j.size.size(); ++i){
        if (j.size[i] <= (E[0] / interval_num)) {
            nfinterval1.add_job(j);
        } else if ((E[0] / interval_num) < j.size[i] && j.size[i]<= (E[0] / (interval_num - 1))) {
            nfinterval2.add_job(j);
        } else if ((E[0] / (interval_num - 1)) < j.size[i] && j.size[i] <= (E[0] / (interval_num - 2))) {
            nfinterval3.add_job(j);
        } else if ((E[0] / (interval_num - 2)) < j.size[i] && j.size[i] <= (E[0] / (interval_num - 3))) {
            nfinterval4.add_job(j);
        } else if ((E[0] / (interval_num - 3)) < j.size[i] && j.size[i] <= (E[0] / (interval_num - 4))) {
            nfinterval5.add_job(j);
        } else if ((E[0] / (interval_num - 4)) < j.size[i] && j.size[i] <= (E[0] / (interval_num - 5))) {
            nfinterval6.add_job(j);
        } else if ((E[0] / (interval_num - 5)) < j.size[i] && j.size[i] <= (E[0] / (interval_num - 6))) {
            nfinterval7.add_job(j);
        } else if ((E[0] / (interval_num - 6)) < j.size[i] && j.size[i] <= (E[0] / (interval_num - 7))) {
            nfinterval8.add_job(j);
        } else if ((E[0] / (interval_num - 7)) < j.size[i] && j.size[i] <= (E[0] / (interval_num - 8))) {
            nfinterval9.add_job(j);
        } else if ((E[0] / (interval_num - 8)) < j.size[i] && j.size[i] <= E[0]) {
            nfinterval10.add_job(j);
        }

    }   
}
    void print_servers(){
        cout << "************** First Interval Jobs ******************"<<endl;
        nfinterval1.print_servers();
        cout << "************** Second Interval Jobs ******************"<<endl;
        nfinterval2.print_servers();
        cout << "************** Third Interval Jobs ******************"<<endl;
        nfinterval3.print_servers();
        cout << "************** Forth Interval Jobs ******************"<<endl;
        nfinterval4.print_servers();
        cout << "************** Fifth Interval Jobs ******************"<<endl;
        nfinterval5.print_servers();
        cout << "************** Sixth Interval Jobs ******************"<<endl;
        nfinterval6.print_servers();
        cout << "************** Seventh Interval Jobs ******************"<<endl;
        nfinterval7.print_servers();
        cout << "************** eight Interval Jobs ******************"<<endl;
        nfinterval8.print_servers();
        cout << "************** nine Interval Jobs ******************"<<endl;
        nfinterval9.print_servers();
        cout << "************** ten Interval Jobs ******************"<<endl;
        nfinterval10.print_servers();
    }

    long long cost(){
        return nfinterval1.cost() + nfinterval2.cost()+ nfinterval3.cost()+ nfinterval4.cost()+nfinterval5.cost()+ nfinterval6.cost() + nfinterval7.cost()+ nfinterval8.cost()+ nfinterval9.cost()+ nfinterval10.cost();
    }

};




// class Greedy {
// public:
    
//     vector<Server> all_servers;
//     vector<int> active_servers_idx;
//     int cur_time;
//     int capacity;

//     Greedy(int _capacity) : cur_time(0), capacity(_capacity) {}

// void add_job(Job& j) {
//     assert(j.start >= cur_time);
//     cur_time = j.start;

//     Server* best_server = nullptr;
//     int best_extension = std::numeric_limits<int>::max();

//     // Remove inactive servers
//     auto it = active_servers_idx.begin();
//     while (it != active_servers_idx.end()) {
//         if (!all_servers[*it].advance_time(cur_time)) {
//             it = active_servers_idx.erase(it);
//         } else {
//             ++it;
//         }
//     }

//     // Find the best server for the job
//     for (const int idx : active_servers_idx) {
//         int extension;
//         if (all_servers[idx].get_server_finishing_time() < j.end) {
//             // The job finishes after the server's current finishing time
//             extension = j.end - all_servers[idx].get_server_finishing_time();
//         } else {
//             // The job finishes before the server's current finishing time
//             extension = 0;
//         }

//         if (extension < best_extension && all_servers[idx].remaining_capacity() >= j.size) {
//             best_extension = extension;
//             best_server = &all_servers[idx]; // Assign pointer to the server, not the index
//         }
//     }

//     if (best_server) {
//         best_server->add_job(j);
//     } else {
//         // If no server can accommodate the job, create a new server
//         Server new_server(j, capacity);
//         all_servers.push_back(new_server);
//         active_servers_idx.push_back(all_servers.size() - 1);
//     }
// }

//     void print_servers() {
//         cout << "------------------ GREEDY STATUS BEGIN ------------------" << endl;
//         for (int i = 0; i < all_servers.size(); i++) {
//             cout << "*** status of server " << i + 1 << " ***" << endl;
//             all_servers[i].print_status();
//         }
//         cout << "------------------ GREEDY STATUS END ------------------" << endl;
//     }

//     long long cost() {
//         long long res = 0;
//         for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
//             res += (*it).duration();
//         }
//         return res;
//     }
// };


class Greedy_dimensional {
public:
    
    vector<Server_dimensional> all_servers;
    vector<int> active_servers_idx;
    int cur_time;
     std::vector<int> capacity;

    Greedy_dimensional(const std::vector<int>& _capacity) : cur_time(0), capacity(_capacity) {}

    void add_job(Job_dimensional& j) {
        assert(j.start >= cur_time);
        cur_time = j.start;

        Server_dimensional* best_server = nullptr;
        int best_extension = std::numeric_limits<int>::max();

        // Remove inactive servers
        auto it = active_servers_idx.begin();
        while (it != active_servers_idx.end()) {
            if (!all_servers[*it].advance_time(cur_time)) {
                it = active_servers_idx.erase(it);
            } else {
                ++it;
            }
        }

        // Find the best server for the job
        for (const int idx : active_servers_idx) {
            int extension;
            if (all_servers[idx].get_server_finishing_time() < j.end) {
                // The job finishes after the server's current finishing time
                extension = j.end - all_servers[idx].get_server_finishing_time();
            } else {
                // The job finishes before the server's current finishing time
                extension = 0;
            }

            if (extension < best_extension) {
                bool enoughCapacity = true;
                for (size_t i = 0; i < j.size.size(); ++i) {
                    if (all_servers[idx].remaining_capacity()[i] < j.size[i]) {
                        enoughCapacity = false;
                        break;
                    }
                }

                if (enoughCapacity) {
                    best_extension = extension;
                    best_server = &all_servers[idx];
                }
            }
        }

        if (best_server) {
            best_server->add_job(j);
        } else {
            // If no server can accommodate the job, create a new server
            Server_dimensional new_server(j, capacity);
             all_servers.push_back(new_server);
            active_servers_idx.push_back(static_cast<int>(all_servers.size()) - 1);

        }
    }

    void print_servers() {
        cout << "------------------ GREEDY STATUS BEGIN ------------------" << endl;
        for (int i = 0; i < all_servers.size(); i++) {
            cout << "*** status of server " << i + 1 << " ***" << endl;
            all_servers[i].print_status();
        }
        cout << "------------------ GREEDY STATUS END ------------------" << endl;
    }

    long long cost() {
        long long res = 0;
        for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
            res += (*it).duration();
        }
        return res;
    }
};



// class RandomFit {
// public:

//     vector<Server> all_servers;
//     vector<int> active_servers_idx;
//     int cur_time;
//     int capacity;
//     random_device rd;
//     mt19937 gen;

//     RandomFit(int _capacity) : cur_time(0),capacity(_capacity), gen(rd()) {}

//     void add_job(Job& j) {
//     assert(j.start >= cur_time); // Jobs should be added by non-decreasing start times

//     // Advance time for RF and all its servers and update active_server_idx
//     cur_time = j.start;

//     // Update the time for active servers and remove inactive servers
//     auto it = active_servers_idx.begin();
//     while (it != active_servers_idx.end()) {
//         if (!all_servers[*it].advance_time(cur_time)) {
//             it = active_servers_idx.erase(it);
//         } else {
//             ++it;
//         }
//     }

//     // Randomly select an active server that can accommodate the job (if any) or create a new server
//     vector<int> shuffled_servers = active_servers_idx;
//     std::shuffle(shuffled_servers.begin(), shuffled_servers.end(), gen);
    
//     bool job_assigned = false;
//     for (int server_index : shuffled_servers) {
//         if (all_servers[server_index].remaining_capacity() >= j.size) {
//             Server* random_server = &all_servers[server_index];
//             random_server->add_job(j);
//             job_assigned = true;
//             break;
//         }
//     }

//     if (!job_assigned) {
//         // If no active server can accommodate the job, open a new server
//         Server new_server(j, capacity);
//         all_servers.push_back(new_server);
//         active_servers_idx.push_back(all_servers.size() - 1); // Add the new server to active_servers_idx
//     }
// }
//     void print_servers() {
//         std::cout << "------------------ RANDOM FIT STATUS BEGIN ------------------" << std::endl;
//         for (size_t i = 0; i < all_servers.size(); i++) {
//             std::cout << "*** status of server " << i + 1 << " ***" << std::endl;
//             all_servers[i].print_status();
//         }
//         std::cout << "------------------ RANDOM FIT STATUS END ------------------" << std::endl;
//     }

//     long long cost() {
//         long long res = 0;
//         for (auto it = all_servers.begin(); it != all_servers.end(); it++) {
//             res += (*it).duration();
//         }
//         return res;
//     }
// };


class RandomFit_dimensional {
public:

    vector<Server_dimensional> all_servers;
    vector<int> active_servers_idx;
    int cur_time;
    std::vector<int> capacity;
    random_device rd;
    mt19937 gen;

    RandomFit_dimensional(const std::vector<int>& _capacity) : cur_time(0),capacity(_capacity), gen(rd()) {}

    void add_job(Job_dimensional& j) {
        assert(j.start >= cur_time); // Jobs should be added by non-decreasing start times

        // Advance time for RF and all its servers and update active_server_idx
        cur_time = j.start;

        // Update the time for active servers and remove inactive servers
        auto it = active_servers_idx.begin();
        while (it != active_servers_idx.end()) {
            if (!all_servers[*it].advance_time(cur_time)) {
                it = active_servers_idx.erase(it);
            } else {
                ++it;
            }
        }

        // Randomly select an active server that can accommodate the job (if any) or create a new server
        vector<int> shuffled_servers = active_servers_idx;
        std::shuffle(shuffled_servers.begin(), shuffled_servers.end(), gen);
    
        bool job_assigned = false;
        for (int server_index : shuffled_servers) {
            bool enoughCapacity = true;
            std::vector<int> remaining_capacity = all_servers[server_index].remaining_capacity();

            for (size_t i = 0; i < j.size.size(); ++i) {
                if (remaining_capacity[i] < j.size[i]) {
                    enoughCapacity = false;
                    break;
                }
            }

            if (enoughCapacity) {
                Server_dimensional* random_server = &all_servers[server_index];
                random_server->add_job(j);
                job_assigned = true;
                break;
            }
        }

        if (!job_assigned) {
            // If no active server can accommodate the job, open a new server
            Server_dimensional new_server(j, capacity);
            all_servers.push_back(new_server);
            active_servers_idx.push_back(all_servers.size() - 1); // Add the new server to active_servers_idx
        }
    }
    void print_servers() {
        std::cout << "------------------ RANDOM FIT STATUS BEGIN ------------------" << std::endl;
        for (size_t i = 0; i < all_servers.size(); i++) {
            std::cout << "*** status of server " << i + 1 << " ***" << std::endl;
            all_servers[i].print_status();
        }
        std::cout << "------------------ RANDOM FIT STATUS END ------------------" << std::endl;
    }

    long long cost() {
        long long res = 0;
        for (auto it = all_servers.begin(); it != all_servers.end(); it++) {
            res += (*it).duration();
        }
        return res;
    }
};

// class RandomAssign{
//     public:

//     vector<Server> all_servers;
//     vector<int> active_servers_idx;
//     int cur_time;
//     int capacity;
//     random_device rd;
//     mt19937 gen;

//     RandomAssign(int _capacity) : cur_time(0),capacity(_capacity), gen(rd()) {}

//     void add_job(Job &j){
//         assert(j.start >= cur_time);

//         cur_time = j.start;

//         auto it = active_servers_idx.begin();
//         while (it != active_servers_idx.end()) {
//             if (!all_servers[*it].advance_time(cur_time)) {
//                 it = active_servers_idx.erase(it);
//             } else {
//                 ++it;
//             }
//         }

//         // Coin flip
//         bool coin_flip = (rand() % 2 == 1);

//         if (coin_flip) {
//             // Randomly select an active server that can accommodate the job (if any) or create a new server
//             vector<int> shuffled_servers = active_servers_idx;
//             std::shuffle(shuffled_servers.begin(), shuffled_servers.end(), gen);

//             bool job_assigned = false;
//             for (int server_index : shuffled_servers) {
//                 if (all_servers[server_index].remaining_capacity() >= j.size) {
//                     Server* random_server = &all_servers[server_index];
//                     random_server->add_job(j);
//                     job_assigned = true;
//                     break;
//                 }
//             }

//             if (!job_assigned) {
//                 // If no active server can accommodate the job, open a new server
//                 Server new_server(j, capacity);
//                 all_servers.push_back(new_server);
//                 active_servers_idx.push_back(all_servers.size() - 1);
//             }
//         } else {
//             // If coin flip is 0, always create a new server and assign the job there
//             Server new_server(j, capacity);
//             all_servers.push_back(new_server);
//             active_servers_idx.push_back(all_servers.size() - 1);
//         }
    
//     }


//     void print_servers() {
//         std::cout << "------------------ RANDOM FIT STATUS BEGIN ------------------" << std::endl;
//         for (size_t i = 0; i < all_servers.size(); i++) {
//             std::cout << "*** status of server " << i + 1 << " ***" << std::endl;
//             all_servers[i].print_status();
//         }
//         std::cout << "------------------ RANDOM FIT STATUS END ------------------" << std::endl;
//     }

//     long long cost() {
//         long long res = 0;
//         for (auto it = all_servers.begin(); it != all_servers.end(); it++) {
//             res += (*it).duration();
//         }
//         return res;
//     }

// };



// class WorstFit {
// public:
//     vector<Server> all_servers;
//     vector<int> active_servers_idx;
//     int cur_time;
//     int capacity;

//     WorstFit(int _capacity) : cur_time(0), capacity(_capacity) {}


//     void add_job(Job& j) {
//         assert(j.start >= cur_time); // Jobs should be added by non-decreasing start times

//         // Advance time for Worst Fit and all its servers and update active_server_idx
//         cur_time = j.start;

//         auto it = active_servers_idx.begin();
//         while (it != active_servers_idx.end()) {
//             if (!all_servers[*it].advance_time(cur_time)) {
//                 it = active_servers_idx.erase(it);
//                 continue;
//             } else {
//                 ++it;
//             }
//         }

//         // Find the server with the maximum remaining capacity
//         int max_remain_capacity_idx = -1;
//         it = active_servers_idx.begin();
//         while (it != active_servers_idx.end()) {
//             if (all_servers[*it].remaining_capacity() >= j.size &&
//                 (max_remain_capacity_idx == -1 || all_servers[*it].remaining_capacity() > all_servers[max_remain_capacity_idx].remaining_capacity())) {
//                 max_remain_capacity_idx = *it;
//             }
//             ++it;
//         }

//         if (max_remain_capacity_idx != -1) {
//             all_servers[max_remain_capacity_idx].add_job(j);
//         } else {

//             // If no active server has enough capacity, create a new server
//             all_servers.push_back(Server(j, capacity));
//             int newIndex = static_cast<int>(all_servers.size()) - 1;
//             active_servers_idx.push_back(newIndex);
//         }
//     }

//         void print_servers() {
//         cout << "------------------Worst FIT STATUS BEGIN ----------------------" << endl;
//         int server_num = 1;
//         for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
//             cout << "*** status of server " << server_num << " ***" << endl;
//             server_num++;
//             (*it).print_status();
//         }
//         cout << "------------------Worst FIT STATUS END ------------------------" << endl;
//     }

//     long long cost() {
//         long long res = 0;
//         for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
//             res += (*it).duration();
//         }
//         return res;
//     }
// };

class WorstFit_dimensional {
public:
    vector<Server_dimensional> all_servers;
    vector<int> active_servers_idx;
    int cur_time;
    std::vector<int> capacity;


    WorstFit_dimensional(const std::vector<int>& _capacity) : cur_time(0), capacity(_capacity) {}


    void add_job(Job_dimensional& j) {
        assert(j.start >= cur_time); // Jobs should be added by non-decreasing start times

        // Advance time for Worst Fit and all its servers and update active_server_idx
        cur_time = j.start;

        auto it = active_servers_idx.begin();
        while (it != active_servers_idx.end()) {
            if (!all_servers[*it].advance_time(cur_time)) {
                it = active_servers_idx.erase(it);
                continue;
            } else {
                ++it;
            }
        }

        // Find the server with the maximum remaining capacity
        int max_remain_capacity_idx = -1;
        it = active_servers_idx.begin();
        while (it != active_servers_idx.end()) {
            bool enoughCapacity = true;
            std::vector<int> remaining_capacity = all_servers[*it].remaining_capacity();

            for (size_t i = 0; i < j.size.size(); ++i) {
                if (remaining_capacity[i] < j.size[i]) {
                    enoughCapacity = false;
                    break;
                }
            }

            if (enoughCapacity) {
                if (max_remain_capacity_idx == -1 || remaining_capacity > all_servers[max_remain_capacity_idx].remaining_capacity()) {
                    max_remain_capacity_idx = *it;
                }
            }
            ++it;
        }

        if (max_remain_capacity_idx != -1) {
            all_servers[max_remain_capacity_idx].add_job(j);
        } else {

            // If no active server has enough capacity, create a new server
            Server_dimensional new_server(j, capacity);
            all_servers.push_back(new_server);
            int newIndex = static_cast<int>(all_servers.size()) - 1;
            active_servers_idx.push_back(newIndex);
        }
    }

        void print_servers() {
        cout << "------------------Worst FIT STATUS BEGIN ----------------------" << endl;
        int server_num = 1;
        for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
            cout << "*** status of server " << server_num << " ***" << endl;
            server_num++;
            (*it).print_status();
        }
        cout << "------------------Worst FIT STATUS END ------------------------" << endl;
    }

    long long cost() {
        long long res = 0;
        for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
            res += (*it).duration();
        }
        return res;
    }
};

// class LastFit {
// public:
//     vector<Server> all_servers;
//     vector<int> active_servers_idx;
//     int cur_time;
//     int capacity;

//     LastFit(int _capacity): cur_time(0), capacity(_capacity) {}

//     void add_job(Job &j) {
//         assert(j.start >= cur_time); // jobs should be added by non-decreasing start times
//         cur_time = j.start;

//         bool placed = false;
//         typeof(active_servers_idx.rbegin()) it = active_servers_idx.rbegin();
//         while(it != active_servers_idx.rend() && !placed) {
//             // try placing job in the current server
//             placed = all_servers[*it].add_job(j);
//             if(!placed) {
//                 // check if a server is still active
//                 if(all_servers[*it].is_active) {
//                     it++;
//                 } else {
//                     it = decltype(active_servers_idx.rbegin()) (active_servers_idx.erase(std::next(it).base()));

//                     //it = active_servers_idx.erase(it);
//                 }
//             }
//         }
//         // If not placed, create a new server
//         if (!placed) {
//             all_servers.push_back(Server(j, capacity));
//             active_servers_idx.push_back((int) all_servers.size()-1);
//         }
//     }

//     void print_servers() {
//         cout << "------------------FIRST FIT STATUS BEGIN ----------------------" << endl;
//         int server_num = 1;
//         for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
//             cout << "*** status of server " << server_num << " ***" << endl;
//             server_num++;
//             (*it).print_status();
//         }
//         cout << "------------------FIRST FIT STATUS END ------------------------" << endl;
//     }

//     long long cost() {
//         long long res = 0;
//         for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
//             res += (*it).duration();
//         }
//         return res;
//     }
// };

class LastFit_dimensional {
public:
    vector<Server_dimensional> all_servers;
    vector<int> active_servers_idx;
    int cur_time;
    std::vector<int> capacity;

    LastFit_dimensional(const std::vector<int>& _capacity): cur_time(0), capacity(_capacity) {}

    void add_job(Job_dimensional &j) {
        assert(j.start >= cur_time); // jobs should be added by non-decreasing start times
        cur_time = j.start;

        bool placed = false;
        typeof(active_servers_idx.rbegin()) it = active_servers_idx.rbegin();
        while(it != active_servers_idx.rend() && !placed) {
            // try placing job in the current server
            placed = all_servers[*it].add_job(j);
            if(!placed) {
                // check if a server is still active
                if(all_servers[*it].is_active) {
                    it++;
                } else {
                    it = decltype(active_servers_idx.rbegin()) (active_servers_idx.erase(std::next(it).base()));

                    //it = active_servers_idx.erase(it);
                }
            }
        }
        // If not placed, create a new server
        if (!placed) {
            all_servers.push_back(Server_dimensional(j, capacity));
            active_servers_idx.push_back(static_cast<int> (all_servers.size())-1);
        }
    }

    void print_servers() {
        cout << "------------------FIRST FIT STATUS BEGIN ----------------------" << endl;
        int server_num = 1;
        for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
            cout << "*** status of server " << server_num << " ***" << endl;
            server_num++;
            (*it).print_status();
        }
        cout << "------------------FIRST FIT STATUS END ------------------------" << endl;
    }

    long long cost() {
        long long res = 0;
        for(typeof(all_servers.begin()) it = all_servers.begin(); it != all_servers.end(); it++) {
            res += (*it).duration();
        }
        return res;
    }
};


class DepartureStrategy{
    public:
    // DepartureStrategy(const std::vector<int>& _capacity, long long _total_span, int _intervals_length);
    vector<int> capacity;
    long long total_span;
    int intervals_length;
    vector<tuple<int, int> > _intervals;
    std::map<std::tuple<int, int>, std::vector<Job_dimensional>> mapJobs;
    std::map<std::tuple<int, int>, FirstFit_dimensional*> mapFirstFits;
   

    DepartureStrategy(const std::vector<int>& _capacity, long long _total_span, int _intervals_length): capacity(_capacity), total_span(_total_span), intervals_length(_intervals_length) {
        _intervals = divide_span_into_intervals(total_span, intervals_length);
    }

    std::vector<std::tuple<int, int>> divide_span_into_intervals(int total_span, int interval_length) {
        // Calculate the number of intervals
        long long num_intervals = total_span / interval_length;
        //std::cout<<"num_intervals"<< num_intervals<<std::endl;

        // Initialize a vector to store the intervals
        std::vector<std::tuple<int, int>> intervals;

        // Determine the boundaries of each interval
        for (int i = 0; i <= num_intervals; ++i) {
            int lower_boundary = i * interval_length;
            int upper_boundary = (i + 1) * interval_length;
            intervals.push_back(std::make_tuple(lower_boundary, upper_boundary));
            //std::cout<< "left_interval:"<< lower_boundary <<std::endl;
            //std::cout<< "right_interval:"<< upper_boundary <<std::endl; 
        }

        // for (int j = 0; j< intervals.size(); j++){
        //     std::cout<< "intervals: (" << std::get<0>(intervals[j]) << ", " << std::get<1>(intervals[j]) << ")" << std::endl;
        // }
        return intervals;
    }

    void addJob(Job_dimensional& j) {
        // Calculate the interval for the job based on its finishing time
        for (const auto& interval : _intervals) {
            if (j.end >= std::get<0>(interval) && j.end < std::get<1>(interval)) {
                // Add the job to mapJobs with the interval as the key
                mapJobs[interval].push_back(j);

                // Check the map for the same interval in mapFirstFits
                if (mapFirstFits.count(interval) == 0) {
                    // If the interval does not exist in mapFirstFits, create a new FirstFit instance for it
                    mapFirstFits[interval] = new FirstFit_dimensional(capacity);
                }

                // Add the job to the corresponding FirstFit instance
                mapFirstFits[interval]->add_job(j);


                // Print the contents of mapJobs after adding the job
                // std::cout << "Contents of mapJobs after adding the job:" << std::endl;
                // for (const auto& entry : mapJobs) {
                //     const std::tuple<int, int>& interval = entry.first;
                //     const std::vector<Job>& jobs = entry.second;

                //     int lower_boundary = std::get<0>(interval);
                //     int upper_boundary = std::get<1>(interval);

                //     std::cout << "Interval: (" << lower_boundary << ", " << upper_boundary << "):" << std::endl;

                //     for (const Job& job : jobs) {
                //         std::cout << "  Job size: " << job.size << " Start: " << job.start << " End: " << job.end << std::endl;
                //     }
                // }

                break; // Break the loop after adding to the correct interval.
            }
        }
    }

// long long DepartureStrategy::getCost()
// {
//     long long total_cost;
//     for (auto &firstFit : mapFirstFits)
//     {
//         long long cost = firstFit.second->getCost();
//         //std::cout << "type: " << firstFit.first << " | cost: " << cost << std::endl;
//         total_cost += cost;
//     }
//     return total_cost;
// }

    long long getCost()
    {
        long long total_cost = 0;

        for (const auto& pair : mapFirstFits)
        {
            if (pair.second) {
                long long cost = pair.second->cost();
                total_cost += cost;
            }
        }

        return total_cost;
    }


};




class HybridAlgorithm {
    public:
        std::map<long long, std::vector<Job_dimensional> > mapJobs;
        std::map<long long, FirstFit_dimensional *> mapFirstFits;
        FirstFit_dimensional *firstFit;
        vector<int> capacity;

        long totalSizeActiveJobs; // d

        // HybridAlgorithm(int _capacity);

        // std::pair<long long, long long> calculateParameters(const Job_dimensional &job);
        // long long cantor_encode(long long i, long long c);
        // std::pair<int, int> cantor_decode(long long type_name);
        // void addJob(Job_dimensional &j);        
        // long long getCost();

        HybridAlgorithm(vector<int> _capacity)
        {
            firstFit = new FirstFit_dimensional(_capacity);
            capacity = _capacity;
        }

        std::pair<long long, long long> calculateParameters(const Job_dimensional &job)
        {
            long long i = static_cast<int>(floor(log2(job.end - job.start))) + 1;
            long long c = static_cast<long long>(floor(job.start / pow(2, i - 1)));
            return std::make_pair(i, c);
        }

        long long cantor_encode(long long i, long long c)
        {
            long long type_name;
            if (i >= 0 && c >= 0)
            {
                type_name = (i + c) * (i + c + 1) / 2 + c;
            }
            else
            {
                std::cout << "ERROR";
            }
            return type_name;
        }

        std::pair<int, int> cantor_decode(long long type_name)
        {
            int w, t;
            long long i, c;

            w = floor(((sqrt((type_name * 8) + 1)) - 1) / 2);
            t = (w * (w + 1)) / 2;
            c = type_name - t;
            i = w - c;

            return std::make_pair(i, c);
        }

        void addJob(Job_dimensional &j)
        {
            std::pair<long long, long long> parameters = calculateParameters(j);
            long long _i = parameters.first;
            long long _c = parameters.second;
            long long typeName = cantor_encode(_i, _c);
            
            // calculate d
            // iterate over the j.size
            for (size_t i = 0; i < j.size.size(); ++i)
            {
                totalSizeActiveJobs += j.size[i];

                totalSizeActiveJobs = 0;
                if (mapJobs.size() == 0)
                {
                    
                    totalSizeActiveJobs = j.size[i];
                }
                else
                {
                    if (mapJobs.find(typeName) != mapJobs.end())
                    {
                        for (auto &job_arrived : mapJobs.at(typeName))
                        {
                            if (j.start >= job_arrived.start && j.start <= job_arrived.end)
                            {
                                totalSizeActiveJobs += job_arrived.size[i];
                            }
                        }
                    }
                    else
                    {
                        totalSizeActiveJobs = j.size[i];
                    }
                }
            }

            // check the map for the same type_name
            if (mapFirstFits.size() != 0 && mapFirstFits.count(typeName) > 0)
            {
                // existent
                mapFirstFits.at(typeName)->add_job_active(j);
            }
            else if (totalSizeActiveJobs <= 1 / (2 * sqrt(_i)))
            {
                // general
                firstFit->add_job(j);
            }
            else
            {
                // new
                mapFirstFits.insert(std::make_pair(typeName, new FirstFit_dimensional(capacity)));
                mapFirstFits.at(typeName)->add_job(j);
            }

        }

        long long getCost()
        {
            long long total_cost = firstFit->cost();
            for (auto &firstFit : mapFirstFits)
            {
                long long cost = firstFit.second->cost();
                // std::cout << "type: " << firstFit.first << " | cost: " << cost << std::endl;
                total_cost += cost;
            }
            return total_cost;
        }

};

// void test_server() {
//     int capacity = 100;
//     Job j1(10, 40, 40);
//     Job j2(15, 35, 70);
//     Job j3(16, 35, 40);
//     Job j4(34, 75, 1);
//     Server s(j1, capacity);
//     s.print_status();
//     cout << " Adding job " << j2.start << ", " << j2.end << ", " << j2.size << endl;
//     cout << " Is adding successfull: " << s.add_job(j2) << endl;
//     s.print_status();
//     cout << " Adding job " << j3.start << ", " << j3.end << ", " << j3.size << endl;
//     cout << " Is adding successfull: " << s.add_job(j3) << endl;
//     s.print_status();
//     cout << " Advancing time to " << 20 << endl;
//     s.advance_time(20);
//     s.print_status();
//     cout << " Adding job " << j4.start << ", " << j4.end << ", " << j4.size << endl;
//     cout << " Is adding successfull: " << s.add_job(j4) << endl;
//     s.print_status();
// }

// void test_vec_removal() {
//     vector<int> vec;
//     for(int i = 1; i <= 10; i++) {
//         vec.push_back(i);
//     }
//     typeof(vec.begin()) it = vec.begin();
//     while(it != vec.end()) {
//         if(*it % 3 == 0 || *it % 4 == 0)
//             it = vec.erase(it);
//         else
//             it++;
//     }
//     for(int i = 0; i < vec.size(); i++) {
//         cout << vec[i] << endl;
//     }
// }

// void test_next_fit() {
//     int capacity = 100;
//     Job j1(10, 40, 40);
//     Job j2(15, 35, 70);
//     Job j3(16, 35, 10);
//     Job j4(34, 75, 1);
//     Job j5(90, 110, 5);

//     NextFit nf(capacity);

//     nf.add_job(j1);
//     nf.print_servers();
//     nf.add_job(j2);
//     nf.print_servers();
//     nf.add_job(j3);
//     nf.print_servers();
//     nf.add_job(j4);
//     nf.print_servers();
//     nf.add_job(j5);
//     nf.print_servers();

//     cout << "Total cost: " << nf.cost() << endl;


// }


// void test_best_fit() {
//     int capacity = 100;
//     Job j1(10, 40, 40);
//     Job j2(15, 36, 70);
//     Job j3(16, 35, 90);
//     Job j4(36, 75, 1);

//     BestFit bf(capacity);

//     bf.add_job(j1);
//     bf.print_servers();
//     bf.add_job(j2);
//     bf.print_servers();
//     bf.add_job(j3);
//     bf.print_servers();
//     bf.add_job(j4);
//     bf.print_servers();

//     cout << "Total cost: " << bf.cost() << endl;

// }

// void test_random_fit() {
//     int capacity = 100;
//     Job j1(10, 40, 40);
//     Job j2(15, 36, 70);
//     Job j3(16, 35, 65);
//     Job j4(34, 75, 1);

//     RandomFit rf(capacity);

//     rf.add_job(j1);
//     rf.print_servers();
//     rf.add_job(j2);
//     rf.print_servers();
//     rf.add_job(j3);
//     rf.print_servers();
//     rf.add_job(j4);
//     rf.print_servers();

//     cout << "Total cost: " << rf.cost() << endl;

// }

// void test_greedy() {
//     int capacity = 100;
//     Job j1(10, 34, 40);
//     Job j2(15, 36, 70);
//     Job j3(16, 35, 65);
//     Job j4(33, 75, 1);

//     Greedy g(capacity);

//     g.add_job(j1);
//     g.print_servers();
//     g.add_job(j2);
//     g.print_servers();
//     g.add_job(j3);
//     g.print_servers();
//     g.add_job(j4);
//     g.print_servers();

//     cout << "Total cost: " << g.cost() << endl;

// }


// void test_worst_fit() {
//     int capacity = 100;
//     Job j1(10, 40, 60);
//     Job j2(15, 34, 70);
//     Job j3(16, 37, 50);
//     Job j4(36, 75, 1);

//     WorstFit wf(capacity);

//     wf.add_job(j1);
//     wf.print_servers();
//     wf.add_job(j2);
//     wf.print_servers();
//     wf.add_job(j3);
//     wf.print_servers();
//     wf.add_job(j4);
//     wf.print_servers();

//     cout << "Total cost: " << wf.cost() << endl;

// }

// void test_modified_next_fit() {
//     int capacity = 100;
//     Job j1(10, 40, 40);
//     Job j2(15, 35, 70);
//     Job j3(16, 35, 10);
//     Job j4(34, 75, 1);
//     ModifiedNextFit mnf(capacity, 50);

//     mnf.add_job(j1);
//     mnf.print_servers();
//     mnf.add_job(j2);
//     mnf.print_servers();
//     mnf.add_job(j3);
//     mnf.print_servers();
//     mnf.add_job(j4);
//     mnf.print_servers();

//     cout << "Total cost: " << mnf.cost() << endl;

// }


// void test_first_fit() {
//     int capacity = 100;
//     Job j1(10, 40, 40);
//     Job j2(15, 35, 70);
//     Job j3(16, 35, 90);
//     Job j4(34, 75, 1);

//     FirstFit ff(capacity);

//     ff.add_job(j1);
//     ff.print_servers();
//     ff.add_job(j2);
//     ff.print_servers();
//     ff.add_job(j3);
//     ff.print_servers();
//     ff.add_job(j4);
//     ff.print_servers();

//     cout << "Total cost: " << ff.cost() << endl;

// }

// void test_MTF() {
//     int capacity = 100;
//     Job j1(10, 40, 40);
//     Job j2(15, 35, 70);
//     Job j3(16, 35, 10);
//     Job j4(34, 75, 1);
//     MTF mtf(capacity);

//     mtf.add_job(j1);
//     mtf.print_servers();
//     mtf.add_job(j2);
//     mtf.print_servers();
//     mtf.add_job(j3);
//     mtf.print_servers();
//     mtf.add_job(j4);
//     mtf.print_servers();

//     cout << "Total cost: " << mtf.cost() << endl;

// }

// void printJobs(const std::vector<Job>& jobs) {
//     for (const Job& job : jobs) {
//         std::cout << "Job(" << job.start << ", " << job.end << ", " << job.size << ")" << std::endl;
//     }
// }

// void test_OPT() {
//     std::vector<Job> list_of_jobs;
//     int E = 1000;
//     list_of_jobs.push_back(Job(10, 40, 40));
//     list_of_jobs.push_back(Job(15, 35, 70));
//     list_of_jobs.push_back(Job(16, 35, 10));
//     list_of_jobs.push_back(Job(50, 75, 1));

//     std::cout << "List of Jobs are: " << std::endl;
//     printJobs(list_of_jobs);
//     Opt opt(list_of_jobs);
//     std::pair<double, double> result = opt.ceilLBandSpan(E);

//     std::cout << "CeilLB: " << result.first << ", Span: " << result.second << std::endl;

// }



/* This function gets a vector of intervals, capacity of bins, number of jobs, a vector of mus, number of trials and also the different
 algorithms as input and then runs each algorithm for the num of trials that are given and then prints upper bound on the avarage 
  competitive ratio (using the ceiling lower bound on opt) as the output.
*/
// void get_ratios(vector<int> Ts, int E, int n, vector<int> mus, int num_trials, vector<string> algs_array ){
//     int nT = Ts.size();
//     int nMus = mus.size();
//     for (const std::string& className : algs_array) {
//         for (int z = 0; z < nT; z++) {
//             int T = Ts[z];
//             for (int y = 0; y < nMus; y++) {
//                 int mu = mus[y];
//                 double rho2 = 0.0;
//                 long long cost_opt = 0;
//                 for (int trial = 0; trial < num_trials; trial++) {
//                     std::vector<Job> jobs = generate_jobs_on_interval(T, mu, E, n);

//                     //calculate the cost of OPT(Ceiling of Volume)
//                     Opt opt(jobs);
//                     std::pair<long long, long long> result = opt.ceilLBandSpan(E);
//                     cost_opt = result.first;


//                     // Create objects based on the class name
//                     if (className == "NextFit") {
//                         NextFit ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho2 += (double) ff.cost() * E / ((long long) cost_opt);
//                     }

//                     else if (className == "ModifiedNextFit") {
//                         ModifiedNextFit ff(E, (E+mu)/(mu+1));
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho2 += (double) ff.cost() * E / ((long long) cost_opt);

//                     }
//                      else if (className == "HarmonicFit") {
//                         HarmonicFit ff(E, 10);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it, E);
//                         }
//                         rho2 += (double) ff.cost() * E / ((long long) cost_opt);

//                     }

//                     else if (className == "ModifiedFirstFit") {
//                         ModifiedFirstFit ff(E, (E+mu)/(mu+7));
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho2 += (double) ff.cost() * E / ((long long) cost_opt);

//                     }
//                     else if (className == "FirstFit") {
//                         FirstFit ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho2 += (double) ff.cost() * E / ((long long) cost_opt);
//                     }
//                     else if (className == "BestFit") {
//                         BestFit ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho2 += (double) ff.cost() * E / ((long long) cost_opt);
//                     }
//                     else if (className == "LastFit") {
//                         LastFit ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho2 += (double) ff.cost() * E / ((long long) cost_opt);
//                     }
//                     else if (className == "RandomFit") {
//                         RandomFit ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho2 += (double) ff.cost() * E / ((long long) cost_opt);
//                     }
//                     else if (className == "WorstFit") {
//                         WorstFit ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho2 += (double) ff.cost() * E / ((long long) cost_opt);
//                     }
//                     else if (className == "Greedy") {
//                          Greedy ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho2 += (double) ff.cost() * E / ((double) cost_opt);
//                     }
//                     else if (className == "MTF") {
//                         MTF ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho2 += (double) ff.cost() * E / ((long long) cost_opt);
//                     }
//                     else if (className == "BIT") {
//                         BIT ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho2 += (double) ff.cost() * E / ((long long) cost_opt);
//                     }
//                     else if (className == "RandomAssign") {
//                         RandomAssign ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho2 += (double) ff.cost() * E / ((long long) cost_opt);
//                     }
//                     else if (className == "New_MTF") {
//                         New_MTF ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho2 += (double) ff.cost() * E / ((long long) cost_opt);
//                     }
//                     else {
//                         std::cout << "Invalid algorithm class name: " << className << std::endl;
//                         continue;
//                     }
//                 }
//                 rho2 /= num_trials;
//                 cout << "Alg = " << className << " T = " << T << " mu = " << mu << " rho2 = " << rho2 << endl;
//             }
//         }
//     }

// }



/* This function gets a vector of intervals, capacity of bins, number of jobs, a vector of mus, number of trials and also the different
 algorithms as input and then runs each algorithm for the num of trials that are given and then prints upper bound on the avarage 
  competitive ratio (lower bound on opt) as the output.
*/
// void get_ratios_without_ceiling(vector<int> Ts, int E, int n, vector<int> mus, int num_trials, vector<string> algs_array ){
//     int nT = Ts.size();
//     int nMus = mus.size();
//     for (const std::string& className : algs_array) {
//         for (int z = 0; z < nT; z++) {
//             int T = Ts[z];
//             for (int y = 0; y < nMus; y++) {
//                 int mu = mus[y];
//                 double rho = 0.0;
//                 long long cost_opt = 0;
//                 for (int trial = 0; trial < num_trials; trial++) {
//                     std::vector<Job> jobs = generate_jobs_on_interval(T, mu, E, n);

//                     // Create objects based on the class name
//                     if (className == "NextFit") {
//                         NextFit ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho += (double) ff.cost() * E / ((double) volume(jobs));
//                     }

//                     else if (className == "ModifiedNextFit") {
//                         ModifiedNextFit ff(E, (E+mu)/(mu+1));
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho += (double) ff.cost() * E / ((double) volume(jobs));

//                     }
//                      else if (className == "HarmonicFit") {
//                         HarmonicFit ff(E, 10);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it, E);
//                         }
//                         rho += (double) ff.cost() * E / ((double) volume(jobs));

//                     }
//                     else if (className == "ModifiedFirstFit") {
//                         ModifiedFirstFit ff(E, (E+mu)/(mu+7));
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho += (double) ff.cost() * E / ((double) volume(jobs));
//                     }
//                     else if (className == "FirstFit") {
//                         FirstFit ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho += (double) ff.cost() * E / ((double) volume(jobs));
//                     }
//                     else if (className == "BestFit") {
//                         BestFit ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho += (double) ff.cost() * E / ((double) volume(jobs));
//                     }
//                     else if (className == "LastFit") {
//                         LastFit ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho += (double) ff.cost() * E / ((double) volume(jobs));
//                     }
//                     else if (className == "RandomFit") {
//                         RandomFit ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho += (double) ff.cost() * E / ((double) volume(jobs));
//                     }
//                     else if (className == "WorstFit") {
//                         WorstFit ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho += (double) ff.cost() * E / ((double) volume(jobs));
//                     }
//                     else if (className == "GreedyNew") {
//                          Greedy ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho += (double) ff.cost() * E / ((double) volume(jobs));
//                     }
//                     else if (className == "MTF") {
//                         MTF ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho += (double) ff.cost() * E / ((double) volume(jobs));
//                     }
//                     else if (className == "BIT") {
//                         BIT ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         rho += (double) ff.cost() * E / ((double) volume(jobs));
//                     }
//                     else {
//                         std::cout << "Invalid algorithm class name: " << className << std::endl;
//                         continue;
//                     }
//                 }
//                 rho /= num_trials;

//                 cout << "Alg = " << className << " T = " << T << " mu = " << mu << " rho = " << rho << endl;
//             }
//         }
//     }

// }


/* This function gets a vector of intervals, capacity of bins, number of jobs, a vector of mus, number of trials and also the different
 algorithms as input and then runs each algorithm for the num of trials that are given and then prints upper bound on the avarage 
  competitive ratio (lower bound on opt(waste opt)) as the output.
  */
// void get_new_ratios(vector<int> Ts, int E, int n, vector<int> mus, int num_trials, vector<string> algs_array ){
//     int nT = Ts.size();
//     int nMus = mus.size();
//     for (const std::string& className : algs_array) {
//         for (int z = 0; z < nT; z++) {
//             int T = Ts[z];
//             for (int y = 0; y < nMus; y++) {
//                 int mu = mus[y];
//                 double new_rho = 0.0;
//                 //long long cost_opt = 0;
//                 for (int trial = 0; trial < num_trials; trial++) {
//                     std::vector<Job> jobs = generate_jobs_on_interval(T, mu, E, n);

//                     //calculate the cost of OPT(Based on waste LB)
//                     Opt new_opt(jobs);
//                     long long new_result = new_opt.newLB(E);
//                     //new_cost_opt = new_result.first;


//                     // Create objects based on the class name
//                     if (className == "NextFit") {
//                         NextFit ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         new_rho += (double) ff.cost() * E / ((long long) new_result);
//                     }

//                     else if (className == "ModifiedNextFit") {
//                         ModifiedNextFit ff(E, (E+mu)/(mu+1));
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         new_rho += (double) ff.cost() * E / ((long long) new_result);

//                     }
//                      else if (className == "HarmonicFit") {
//                         HarmonicFit ff(E, 10);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it, E);
//                         }
//                         new_rho += (double) ff.cost() * E / ((long long) new_result);

//                     }

//                     else if (className == "ModifiedFirstFit") {
//                         ModifiedFirstFit ff(E, (E+mu)/(mu+7));
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         new_rho += (double) ff.cost() * E / ((long long) new_result);

//                     }
//                     else if (className == "FirstFit") {
//                         FirstFit ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         new_rho += (double) ff.cost() * E / ((long long) new_result);
//                     }
//                     else if (className == "BestFit") {
//                         BestFit ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         new_rho += (double) ff.cost() * E / ((long long) new_result);
//                     }
//                     else if (className == "LastFit") {
//                         LastFit ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         new_rho += (double) ff.cost() * E / ((long long) new_result);
//                     }
//                     else if (className == "RandomFit") {
//                         RandomFit ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         new_rho += (double) ff.cost() * E / ((long long) new_result);
//                     }
//                     else if (className == "WorstFit") {
//                         WorstFit ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         new_rho += (double) ff.cost() * E / ((long long) new_result);
//                     }
//                     else if (className == "Greedy") {
//                          Greedy ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         new_rho += (double) ff.cost() * E / ((double) new_result);
//                     }
//                     else if (className == "MTF") {
//                         MTF ff(E);
//                         for (auto it = jobs.begin(); it != jobs.end(); it++) {
//                             ff.add_job(*it);
//                         }
//                         new_rho += (double) ff.cost() * E / ((long long) new_result);
//                     }
//                     else {
//                         std::cout << "Invalid algorithm class name: " << className << std::endl;
//                         continue;
//                     }
//                 }
//                 new_rho /= num_trials;
//                 cout << "Alg = " << className << " T = " << T << " mu = " << mu << " new_rho = " << new_rho << endl;
//             }
//         }
//     }

// }


// void run_shahin_experiment() {
//     //int Ts[] = {1000, 10000, 100000};
//     vector<int> Ts;
//     Ts.push_back(1000);
//     //Ts.push_back(10000);
//     //Ts.push_back(100000);
//     int E = 1000;
//     int n = 10000;
//     int mus[] = {1, 2, 5,10,100};
//     int num_trials = 100;

//     std::vector<std::string> algs_array;
//     //algs_array.push_back("HarmonicFit");
//     //algs_array.push_back("NextFit");
//     //algs_array.push_back("ModifiedNextFit");
//     //algs_array.push_back("FirstFit");
//     //algs_array.push_back("ModifiedFirstFit");
//     //algs_array.push_back("BestFit");
//     //algs_array.push_back("LastFit");
//     //algs_array.push_back("RandomFit");
//     //algs_array.push_back("WorstFit");
//     //algs_array.push_back("Greedy");
//     //algs_array.push_back("MTF");
//     algs_array.push_back("New_MTF");
//     //algs_array.push_back("BIT");
//     //algs_array.push_back("RandomAssign");


//     get_ratios(Ts, E, n, vector<int>(mus, mus+sizeof(mus)/ sizeof(int)), num_trials, algs_array);
//     //get_ratios_without_ceiling(Ts, E, n, vector<int>(mus, mus+sizeof(mus)/ sizeof(int)), num_trials, algs_array);
//     //get_new_ratios(Ts, E, n, vector<int>(mus, mus+sizeof(mus)/ sizeof(int)), num_trials, algs_array);
 
// }






void get_ratios_without_ceiling_dimensional(vector<int> Ts, std::vector<std::vector<int> > Es, int n, vector<int> mus, int num_trials, vector<string> algs_array ){
    int nT = Ts.size();
    int nMus = mus.size();
    int nEs = Es.size();
    for (int k = 0; k < nEs; k++) {
        vector<int> E = Es[k];
        // for (int i = 0; i < E.size(); ++i) {
        //     std::cout << E[i];
        //     if (i < E.size() - 1) {
        //         std::cout << ", ";
        //     }
        // }
        // std::cout << std::endl;
        // exit(0);
         
        for (const std::string& className : algs_array) {
            for (int z = 0; z < nT; z++) {
                int T = Ts[z];
                for (int y = 0; y < nMus; y++) {
                    int mu = mus[y];
                    double rho = 0.0;
                    long long cost_opt = 0;
                    for (int trial = 0; trial < num_trials; trial++) {
                        //std::vector<Job> jobs = generate_jobs_on_interval(T, mu, E, n);
                        std::vector<Job_dimensional> jobs = generate_dimensional_jobs_on_interval(T, mu, E, n);
                        // for (const Job_dimensional& job : jobs) {
                        //     std::cout << "Start Time: " << job.start << ", End Time: " << job.end << ", Sizes: ";
                        //     for (int size : job.size) {
                        //         std::cout << size << " ";
                        //         }
                        //     std::cout << std::endl;
                        // }
                        // exit(0);



                        // Create objects based on the class name
                        if (className == "NextFit_dimensional") {
                            NextFit_dimensional ff(E);
                            for (auto it = jobs.begin(); it != jobs.end(); it++) {
                                ff.add_job(*it);
                            }
                            rho += (double) ff.cost() * 1000 / ((double) volume_dimensional(jobs));
                        }

                        // else if (className == "ModifiedNextFit") {
                        //     ModifiedNextFit ff(E, (E+mu)/(mu+1));
                        //     for (auto it = jobs.begin(); it != jobs.end(); it++) {
                        //         ff.add_job(*it);
                        //     }
                        //     rho += (double) ff.cost() * E / ((double) volume(jobs));

                        // }
                        // else if (className == "HarmonicFit") {
                        //     HarmonicFit ff(E, 10);
                        //     for (auto it = jobs.begin(); it != jobs.end(); it++) {
                        //         ff.add_job(*it, E);
                        //     }
                        //     rho += (double) ff.cost() * E / ((double) volume(jobs));

                        // }
                        // else if (className == "ModifiedFirstFit") {
                        //     ModifiedFirstFit ff(E, (E+mu)/(mu+7));
                        //     for (auto it = jobs.begin(); it != jobs.end(); it++) {
                        //         ff.add_job(*it);
                        //     }
                        //     rho += (double) ff.cost() * E / ((double) volume(jobs));
                        // }
                        // else if (className == "FirstFit") {
                        //     FirstFit ff(E);
                        //     for (auto it = jobs.begin(); it != jobs.end(); it++) {
                        //         ff.add_job(*it);
                        //     }
                        //     rho += (double) ff.cost() * E / ((double) volume(jobs));
                        // }
                        // else if (className == "BestFit") {
                        //     BestFit ff(E);
                        //     for (auto it = jobs.begin(); it != jobs.end(); it++) {
                        //         ff.add_job(*it);
                        //     }
                        //     rho += (double) ff.cost() * E / ((double) volume(jobs));
                        // }
                        // else if (className == "LastFit") {
                        //     LastFit ff(E);
                        //     for (auto it = jobs.begin(); it != jobs.end(); it++) {
                        //         ff.add_job(*it);
                        //     }
                        //     rho += (double) ff.cost() * E / ((double) volume(jobs));
                        // }
                        // else if (className == "RandomFit") {
                        //     RandomFit ff(E);
                        //     for (auto it = jobs.begin(); it != jobs.end(); it++) {
                        //         ff.add_job(*it);
                        //     }
                        //     rho += (double) ff.cost() * E / ((double) volume(jobs));
                        // }
                        // else if (className == "WorstFit") {
                        //     WorstFit ff(E);
                        //     for (auto it = jobs.begin(); it != jobs.end(); it++) {
                        //         ff.add_job(*it);
                        //     }
                        //     rho += (double) ff.cost() * E / ((double) volume(jobs));
                        // }
                        // else if (className == "GreedyNew") {
                        //     Greedy ff(E);
                        //     for (auto it = jobs.begin(); it != jobs.end(); it++) {
                        //         ff.add_job(*it);
                        //     }
                        //     rho += (double) ff.cost() * E / ((double) volume(jobs));
                        // }
                        // else if (className == "MTF") {
                        //     MTF ff(E);
                        //     for (auto it = jobs.begin(); it != jobs.end(); it++) {
                        //         ff.add_job(*it);
                        //     }
                        //     rho += (double) ff.cost() * E / ((double) volume(jobs));
                        // }
                        //else {
                        //    std::cout << "Invalid algorithm class name: " << className << std::endl;
                        //    continue;
                       // }
                    }
                    rho /= num_trials;

                    cout << "Alg = " << className << " T = " << T << " mu = " << mu << " rho = " << rho << endl;
                }
            }


        
        }

}

}

void get_ratios_dimensional(vector<int> Ts, std::vector<std::vector<int> > Es, int n, vector<int> mus, int num_trials, vector<string> algs_array ){
    int nT = Ts.size();
    int nMus = mus.size();
    int nEs = Es.size();
    for (int k = 0; k < nEs; k++) {
        vector<int> E = Es[k];
        for (const std::string& className : algs_array) {
            for (int z = 0; z < nT; z++) {
                int T = Ts[z];
                for (int y = 0; y < nMus; y++) {
                    int mu = mus[y];
                    double rho2 = 0.0;
                    long long cost_opt = 0;
                    long long total_span = 0;
                    for (int trial = 0; trial < num_trials; trial++) {
                        std::vector<Job_dimensional> jobs = generate_dimensional_jobs_on_interval(T, mu, E, n);
                        //calculate the cost of OPT(Ceiling of Volume)
                        Opt_dimensional opt(jobs);
                        std::pair<long long, long long> result = opt.ceilLBandSpan(E);
                        cost_opt = result.first;
                        total_span = result.second;
                        
                        
                        // Create objects based on the class name
                        if (className == "NextFit_dimensional") {
                            NextFit_dimensional ff(E);
                            for (auto it = jobs.begin(); it != jobs.end(); it++) {
                                ff.add_job(*it);
                            }
                           // cout<< "cost ff"<< ff.cost();
                           // exit(0);
                            rho2 += (double) ff.cost() * 1000 / ((long long) cost_opt);
                        }

                        else if (className == "ModifiedNextFit_dimensional") {
                            ModifiedNextFit_dimensional ff(E, (1000+mu)/(mu+1));
                            for (auto it = jobs.begin(); it != jobs.end(); it++) {
                                ff.add_job(*it);
                            }
                            rho2 += (double) ff.cost() * 1000 / ((long long) cost_opt);

                        }
                        else if (className == "HarmonicFit_dimensional") {
                            HarmonicFit_dimensional ff(E, 10);
                            for (auto it = jobs.begin(); it != jobs.end(); it++) {
                                ff.add_job(*it, E);
                            }
                            rho2 += (double) ff.cost() * 1000 / ((long long) cost_opt);
                        }

                        else if (className == "ModifiedFirstFit_dimensional") {
                            ModifiedFirstFit_dimensional ff(E, (1000+mu)/(mu+7));
                            for (auto it = jobs.begin(); it != jobs.end(); it++) {
                                ff.add_job(*it);
                            }
                            rho2 += (double) ff.cost() * 1000 / ((long long) cost_opt);
                        }
                        else if (className == "FirstFit_dimensional") {
                            FirstFit_dimensional ff(E);
                            for (auto it = jobs.begin(); it != jobs.end(); it++) {
                                ff.add_job(*it);
                            }
                            rho2 += (double) ff.cost() * 1000 / ((long long) cost_opt);
                        }
                        else if (className == "BestFit_dimensional") {
                            BestFit_dimensional ff(E);
                            for (auto it = jobs.begin(); it != jobs.end(); it++) {
                                ff.add_job(*it);
                            }
                            rho2 += (double) ff.cost() * 1000 / ((long long) cost_opt);
                        }
                        else if (className == "LastFit_dimensional") {
                            LastFit_dimensional ff(E);
                            for (auto it = jobs.begin(); it != jobs.end(); it++) {
                                ff.add_job(*it);
                            }
                            rho2 += (double) ff.cost() * 1000 / ((long long) cost_opt);
                        }
                        else if (className == "RandomFit_dimensional") {
                            RandomFit_dimensional ff(E);
                            for (auto it = jobs.begin(); it != jobs.end(); it++) {
                                ff.add_job(*it);
                            }
                            rho2 += (double) ff.cost() * 1000 / ((long long) cost_opt);
                        }
                        else if (className == "WorstFit_dimensional") {
                            WorstFit_dimensional ff(E);
                            for (auto it = jobs.begin(); it != jobs.end(); it++) {
                                ff.add_job(*it);
                            }
                            rho2 += (double) ff.cost() * 1000 / ((long long) cost_opt);
                        }
                        else if (className == "Greedy_dimensional") {
                            Greedy_dimensional ff(E);
                            for (auto it = jobs.begin(); it != jobs.end(); it++) {
                            ff.add_job(*it);
                            }
                            rho2 += (double) ff.cost() * 1000 / ((double) cost_opt);
                        }
                        else if (className == "MTF_dimensional") {
                            MTF_dimensional ff(E);
                            for (auto it = jobs.begin(); it != jobs.end(); it++) {
                                ff.add_job(*it);
                            }
                            rho2 += (double) ff.cost() * 1000 / ((long long) cost_opt);
                        }
                        else if (className == "DepartureStrategy") {
                            DepartureStrategy ff(E, total_span, 100);
                            for (auto it = jobs.begin(); it != jobs.end(); it++) {
                                ff.addJob(*it);
                            }
                            rho2 += (double) ff.getCost() * 1000 / ((long long) cost_opt);
                        }
                        else if (className == "HybridAlgorithm") {
                            HybridAlgorithm ff(E);
                            for (auto it = jobs.begin(); it != jobs.end(); it++) {
                                ff.addJob(*it);
                            }
                            rho2 += (double) ff.getCost() * 1000 / ((long long) cost_opt);
                        }                  
                    
                        else {
                            std::cout << "Invalid algorithm class name: " << className << std::endl;
                            continue;
                        }
                    }
                    rho2 /= num_trials;
                    cout << "Alg = " << className << " T = " << T << " mu = " << mu << " rho2 = " << rho2 << endl;
                }
            }
        }
    }
}



//This function consider the case when each job's size is a vector in d-dimensional. 
void run_shahin_experiment_dimensional() {
    //int Ts[] = {1000, 10000, 100000};
    vector<int> Ts;
    Ts.push_back(1000);
    Ts.push_back(10000);
    Ts.push_back(100000);
    std::vector<std::vector<int> > Es;

    Es.push_back(std::vector<int>(1, 1000));
    Es.push_back(std::vector<int>(2, 1000));
    Es.push_back(std::vector<int>(5,1000));
    int nEs = Es.size();
    // for (int k = 0; k < nEs; k++) {
    //     vector<int> E = Es[k];
    //     for (int value : E){
    //         std::cout<< value << endl;
    //     }
    // }
    // cout << "size of Es:" << Es.size()<< endl;
    // for (const auto& innerVector : Es) {
    //     for (int value : innerVector) {
    //         std::cout << value << " ";
    //     }


    //     std::cout << std::endl;
    // }
    // exit(0);
    int n = 10000;
    int mus[] = {1, 2, 5, 10, 100};
    int num_trials = 100;

    std::vector<std::string> algs_array;
    //algs_array.push_back("HarmonicFit_dimensional");
    //algs_array.push_back("NextFit_dimensional");
    //algs_array.push_back("ModifiedNextFit_dimensional");
    //algs_array.push_back("FirstFit_dimensional");
    //algs_array.push_back("ModifiedFirstFit_dimensional");
    //algs_array.push_back("BestFit_dimensional");
    //algs_array.push_back("LastFit_dimensional");
    //algs_array.push_back("RandomFit_dimensional");
    //algs_array.push_back("WorstFit_dimensional");
    // algs_array.push_back("Greedy_dimensional");
    //algs_array.push_back("MTF_dimensional");
    //algs_array.push_back("BIT");
    algs_array.push_back("DepartureStrategy");
    // algs_array.push_back("HybridAlgorithm");


    get_ratios_dimensional(Ts, Es, n, vector<int>(mus, mus+sizeof(mus)/ sizeof(int)), num_trials, algs_array);
    //get_ratios_without_ceiling_dimensional(Ts, Es, n, vector<int>(mus, mus+sizeof(mus)/ sizeof(int)), num_trials, algs_array);
    //get_new_ratios(Ts, E, n, vector<int>(mus, mus+sizeof(mus)/ sizeof(int)), num_trials, algs_array);
 
}

// void run_aniket_experiment(){
//     //int Ts[] = {1000, 10000, 100000};
//     vector<int> Ts;
//     Ts.push_back(1000);
//     int E = 100;
//     int n = 1000;
//     int mus[] = {1}; //{1, 2, 5, 10, 100, 200};
//     int num_trials = 100;

//     std::vector<std::string> algs_array;
//     //algs_array.push_back("NextFit");
//     //algs_array.push_back("ModifiedNextFit");
//     //algs_array.push_back("FirstFit");
//     //algs_array.push_back("BestFit");
//     //algs_array.push_back("LastFit");
//     //algs_array.push_back("RandomFit");
//     //algs_array.push_back("WorstFit");
//     //algs_array.push_back("Greedy");
//     //algs_array.push_back("MTF");
//     get_ratios(Ts, E, n, vector<int>(mus, mus+sizeof(mus)/ sizeof(int)), num_trials, algs_array);

// }





int main() {
    //test_next_fit();
    //vector<Job> jobs = generate_jobs_on_interval(100, 5, 10, 5);
    //print_jobs(jobs);
    //test_vec_removal();
    //test_first_fit();
    //run_shahin_experiment();
    run_shahin_experiment_dimensional();
    //run_aniket_experiment();
    //test_modified_next_fit();
    //test_MTF();
    //test_first_fit();
    //test_best_fit();
    //test_random_fit();
    //test_worst_fit();
    //test_greedy();
    //test_OPT();
    return 0;
}