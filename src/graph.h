#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <list>
#include <vector>

#include "pathiterator.h"
#include "edge.h"
#include "step.h"

class Graph
{
  public:
    Graph(int nVerts, std::string name);
    Edge *getEdge(int, int) const;
    void addEdge(int, int);
    void addEdgeRange(int, int, int length);
    void colourEdge(int, int, int);
    void colourPath(std::vector<Edge *> path, int colour);
    void unColourPath(std::vector<Edge *> path);
    bool vertColoured(int vert, int colour) const;
    bool isDone();
    void finish();
    void run();
    void setCallback( void (*func)(Graph *));
    void setCheckpoint(int seconds);
    std::string toString(int start=1) const;
    void writeAsy(std::string suffix="") const;
    void writeTxt(std::string suffix="") const;
    void writeTxtAll(std::string suffix="") const;
    bool twoFactorTriangle(unsigned int i=0, bool empty=false, unsigned int avoid[][7]=NULL);

    void addStep(Step *s);

  private:
    void doNextStep();
    unsigned int nVerts;
    bool done;
    
    std::vector<Step *> steps;
    unsigned int stepCount;
    void (*callback)(Graph *g);


    void saveCheckpoint();
    void loadCheckpoint();

    bool checkpointing;
    time_t chkTimeInterval;
    time_t lastChk;
    std::string chkFileName;
    unsigned long int *checkpoint;
    bool rampingUp;
    unsigned long int *rampTo;
   
    std::string name;

    // C++ doesn't support variable length multidimensional arrays
    // C++14 standard introduces std::array, but for now we use this mess.
    Edge*** edgeLists;
    std::list<Edge *> allEdges;
    std::vector<std::vector<Edge *>> edgeAdjacency;

    friend class PathIterator;
    friend class Step;
    friend class Cycle;
    friend class CycleFill;
    friend class TwoFactor;
    friend class Path;
};


inline void Graph::unColourPath(std::vector<Edge *> path)
{
  colourPath(path,0);
}

inline bool Graph::isDone()
{
  return done;
}

inline void Graph::finish()
{
  done = true;
}
#endif /* GRAPH_H */
