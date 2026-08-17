#include <cmath>
#include <iostream>
#include <algorithm>
#include <ranges>
#include <span>
#include <iterator>
#include <vector>
#include <cstddef>
#include <print>
#include <unordered_set>
#include <tuple>
#include <filesystem>
#include <spanstream>
#include <functional>
//Linux only for mmap
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <chrono>
//implemernt SoA for faster reading
struct D2 {
    std::vector<int> x{};
    std::vector<int> y{};
    std::size_t count {};

};

struct D3 {
    std::vector<int> x{};
    std::vector<int> y{};
    std::vector<int> z{};
    std::size_t count {};

};

//this will work but jank i.e. if futrue dimension are added to txt file this will not suffice, would need to make more conecpts 
template<typename T>
concept is3D = requires (T t) {
    t.z;
};

//Creating our own hash for tuple of 2 and 3 D
//we can use  hash combine algorithm https://www.youtube.com/watch?v=lNR_AWs0q9w
template <typename T>
void hash_combine(std::size_t& seed, const T& t){
    std::hash<T> hashed;
    seed ^= hashed(t) + 0x9e3779b9 + (seed << 6) + (seed>>2);
}

struct ND_hash{
    template<typename Tuple>
    std::size_t  operator()(const Tuple& t) const {
        std::size_t seed{};
        //std::size_t tuple_size = std::tuple_size_v<Tuple>;
        
        std::apply(
            [&seed](const auto&... args){
                (hash_combine(seed, args), ...);
            }
            ,t);
        return seed;
    }
};

//need to make this one function for both struct
//using template instead  
template<typename T>
void parseVals(std::string_view sv, T& t){
    auto dimension{0uz}; 
    int result{};
    for (auto& c : sv){
        if(c >= '0' && c <= '9'){
            const auto num {c -'0'};
            result += num;
            result *= 10;
        }
        // only , and \n should end a number
        else if(c == ',' || c == '\n'){
            result /= 10;
            switch(++dimension) {
                case 1:
                    t.x.emplace_back(result);
                    break;
                case 2:
                    t.y.emplace_back(result);
                    break;
                case 3:
                    if constexpr (requires {t.z;}) {
                        t.z.emplace_back(result);
                    }
                    break;
                } 
            result ^= result; // make result 0 agin  
        }
    }
}

const bool check3D (std::string_view sv) {
    if( sv.contains('Z') )
        return true;
    else {
        return false;
    }
}



int main(){
    
    D2 D2;
    D3 D3;
    //const auto start {std::chrono::steady_clock::now()};
    std::filesystem::path file{"../FinalProject.txt"};
    auto size {std::filesystem::file_size(file)}; 

    int fd = open(file.c_str(), O_RDONLY); 
    if(fd == -1) 
        return -1; 

    // the goal is to send the file stright to memory
    //and read it as one single char array
    const auto txt = static_cast<char*>(mmap(nullptr,size, PROT_READ,MAP_PRIVATE, fd, 0 ));
    //create a string view of it
    std::string_view txtPtr{txt, size};

    if(close(fd)==-1){
        std::cerr <<"Error closing failed\n";
        return -1;
    }
    
    std::ispanstream isp{txtPtr};
    auto viewer{ isp.span()};
    auto begin {viewer.begin()};

    while(begin != viewer.end()){
        const auto endline = std::ranges::find(begin, std::unreachable_sentinel, '\n');
        std::string_view line {begin, endline+1}; //must have endline+1 to add \n due 
        
        bool D3check {check3D(line)};
        if(D3check){
          D3.count++;
          parseVals(line,D3);
        }
        else {
          
          D2.count++;
          parseVals(line,D2);
        }
        begin = endline+1;
    };

   //const auto end {std::chrono::steady_clock::now()};
   
   
   // IMPLEMENTING Frequency of 2D and 3D points
 // using std::views::zip we can use std::ranges::uniuqe 
   // the problem is that zip is a view i.e a reference to our vectors
   // so it will delete the duplicates in our main struct and we do not want that 
   // we can use std::ranges::uniuqe_copy to get a seperate without effecting our stuct 
   // but we also need to sort before using unique 
   
   // V2 is using std::set 
   // V3 Goal is implemneting unordered set as std::unordered_set
   // hash function can't do multi dimensional containters
   //hash function must be copy constructible 

    auto zipped2D = std::views::zip(D2.x,D2.y);
    const auto Freqstart2D {std::chrono::steady_clock::now()};
    std::unordered_set<std::tuple<int&,int&>,ND_hash> unique2D;
    //std::set<std::tuple<int&,int&>> unique2D;

    std::ranges::copy(zipped2D,std::inserter(unique2D,unique2D.begin()));
    const auto Freqend2D {std::chrono::steady_clock::now()};

    auto zipped3D = std::views::zip(D3.x,D3.y,D3.z);
    //std::set<std::tuple<int&,int&,int&>> unique3D;
    std::unordered_set<std::tuple<int,int,int>,ND_hash> unique3D;

    std::ranges::copy(zipped3D,std::inserter(unique3D,unique3D.begin()));
    const auto Freqstart3D {std::chrono::steady_clock::now()};
    /*
    std::vector<std::tuple<int&,int&,int&>> unique3D;
     std::ranges::copy(zipped3D,std::back_inserter(unique3D));
    std::ranges::sort(unique3D);
    //std::ranges::unique(unique2D);
    unique3D.erase(std::ranges::unique(unique3D).begin(), unique3D.end());
    //std::ranges::unique_copy(zipped3D,std::back_inserter(unique3D) );
    */
    const auto Freqend3D {std::chrono::steady_clock::now()};
    /*
    for(auto i{0uz};i<D3.x.size();++i){
        std::cout<< "[ " << D3.x[i] << ", " <<  D3.y[i] << ", " << D3.z[i] << " ]\n";
    }
    for(auto i{0uz};i<D2.x.size();++i){
        std::cout<< "[ " << D2.x[i] << ", " <<  D2.y[i] << " ]\n ";
    }
    */

    std::cout<<"\nTime it takes for 2D unique_copy: "<<(Freqend2D-Freqstart2D)<<"\n";
    std::println("Orignal 2D Size:{} \nUnique 2D Size: {}", D2.count, unique2D.size());
    std::cout<<"\nTime it takes for 3D unique_copy: "<<(Freqend3D-Freqstart3D)<<"\n";
    std::println("Orignal 3D Size:{} \nUnique 3D Size: {}", D3.count, unique3D.size());

    //calulate farthest distance between two points 
    // since i know that the smallest and largest for both sets 
    // are 0s and 100s we can use these values 
    // they will be the farthest distance
    // realisticlly we should use somthing like convex hull
    // to get the points that are farthest 
    
    auto [min2D,max2D]  {std::ranges::minmax(zipped2D)};
    auto [min3D,max3D]  {std::ranges::minmax(zipped3D)};
    auto dist2D = std::sqrtf( 
        (std::get<0>(max2D)-std::get<0>(min2D))*(std::get<0>(max2D)-std::get<0>(min2D)) 
        + (std::get<1>(max2D)-std::get<1>(min2D))*(std::get<1>(max2D)-std::get<1>(min2D)) 
    );
    auto dist3D = std::sqrtf( 
        (std::get<0>(max3D)-std::get<0>(min3D))*(std::get<0>(max3D)-std::get<0>(min3D)) 
        + (std::get<1>(max3D)-std::get<1>(min3D))*(std::get<1>(max3D)-std::get<1>(min3D)) 
        + (std::get<2>(max3D)-std::get<2>(min3D))*(std::get<2>(max3D)-std::get<2>(min3D)) 
    );
    std::println("The farthest Distance between to points: {} with {} , {} as points",dist2D, min2D,max2D);
    std::println("The farthest Distance between to points: {} with {} , {} as points",dist3D, min3D,max3D);

    return 0; // not needed anymore 
};