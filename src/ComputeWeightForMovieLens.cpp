/**
 * @file ComputeWeight.cpp
 * @brief Implements weight computation using similarity method.
 */
#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<math.h>
#include<map>
#include<set>

/** 
 * @param A One of the two vertices of the edge whose weight will be computed.
 * @param B One of the two vertices of the edge whose weight will be computed.
 * @return Weight of the edge.
 */
float computeWeight(int A,int B){
    
    std::fstream filestream("u.data",std::ios::in);
    
    unsigned long int timestamp;
    int user;
    int movie;
    int rating;
    
    std::string line;
    
    // set of movies rated by A and B individually
    std::set<int> moviesratedbyA;
    std::set<int> moviesratedbyB;
    
    // map of movies and corresponding rating by A and B seperately
    std::map<int, int> ratingbyA;
    std::map<int, int> ratingbyB;
    
    // Create two sets of movies rated by A and B individually
    while(std::getline(filestream,line)){
        std::istringstream stringstream(line);
	stringstream>>user>>movie>>rating>>timestamp;
	if(user==A){
	    moviesratedbyA.insert(movie);
	    ratingbyA[movie]=rating;
	} else if(user==B){
	    moviesratedbyB.insert(movie);
	    ratingbyB[movie]=rating;
	}
    }
    
    std::set<int> intersectionofAandB;
    
    // find set of movies rated by both A and B
    std::set_intersection(moviesratedbyA.begin(),moviesratedbyA.end(),moviesratedbyB.begin(),moviesratedbyB.end(),intersectionofAandB.begin())
    
    // Read each line, check if it is intersection, then compute the similarity.
    unsigned long int sumofsquaredrating=0;
    for(std::set<int>::iterator i=intersectionofAandB.begin();i!=intersectionofAandB.end();i++){
	sumofsquaredrating+=pow((ratingbyA.find(*i)-ratingB.find(*i)),2);
    }
    
    double similarity=sumofsquaredrating/intersectionofAandB.size();
    
    return (1.0/(1.0+sqrt(similarity)));
}