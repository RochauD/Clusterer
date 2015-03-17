#ifndef _VERTEX_CLASS_H
#define _VERTEX_CLASS_H

#include <string>
#include <vector>

typedef struct info{
   std::string name;
   int value;
   std::string social_net;
} info;

typedef uint64_t VertexId;
typedef uint64_t ClusterId;

class Vertex{
   private:
      int number;
      bool numberFlag = true;
      info v_info;
      std::vector<Vertex> neighbors;
   public:
      Vertex();
   	  Vertex(int);
   	  Vertex(const Vertex&);
   	  ~Vertex();
   	  int getVNumber() const;
      info getVInfo();
      bool getVNumberFlag();
      void setVNumber(int);
      void setVInfo(const info&);
      void addNeighbor(const Vertex&);
      bool hasNeighbor(Vertex&);
      bool operator==(Vertex&);
};

#endif // _VERTEX_CLASS_H
