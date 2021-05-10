#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <cmath>
#include <iostream>
#include <unordered_map>

//not functional yet, but close!

class Graph {
  //I'll be using adjacency matrix implementation
  //I have also tried to comment my code to make it as readable and understandable as possible :)
private:
    std::vector<std::vector<size_t>> Morpheus; //I use a nested vector as my matrix
    size_t vertexCount;
    size_t edgeCount;
    size_t nextInd;
    std::unordered_map<size_t, size_t> vertsToInds; //I keep track of two seperate unordered maps for optimal access times
    std::unordered_map<size_t, size_t> indsToVerts; //at expense of more memory
    std::unordered_map<size_t, size_t> djikstraData;//this one is to keep track of the results of djikstra, to be used in other functions
    std::vector<std::vector<size_t>> djikstraPaths; //this one is to keep track of the minimum path from the root to given node in graph
    std::vector<size_t> parent;

public:
    Graph() : vertexCount(0), edgeCount(0), nextInd(0){}
    Graph(const Graph& amogus){
        vertexCount = amogus.vertexCount;
        edgeCount = amogus.edgeCount;
        nextInd = amogus.nextInd;
        Morpheus = amogus.Morpheus;
        vertsToInds = amogus.vertsToInds;
        indsToVerts = amogus.indsToVerts;
        djikstraData = amogus.djikstraData;
    }
    Graph& operator=(const Graph& amogus){
        if(this!= &amogus){
            vertexCount = amogus.vertexCount;
            edgeCount = amogus.edgeCount;
            nextInd = amogus.nextInd;
            Morpheus = amogus.Morpheus;
            vertsToInds = amogus.vertsToInds;
            indsToVerts = amogus.indsToVerts;
            djikstraData = amogus.djikstraData;
        }
        return *this;
    }
    ~Graph(){}
    size_t vertex_count() const{
        return vertexCount;
    }
    size_t edge_count() const{
        return edgeCount;
    }
    bool contains_dict(size_t key, std::unordered_map<size_t, size_t> x) const{
        if (x.find(key) == x.end()){
            return false;
        }
        return true;
    }
    bool contains_vertex(size_t id) const{
        if(contains_dict(id, vertsToInds)){
            return true;
        }
        return false;
    }
    bool contains_edge(size_t src, size_t dest) const{
        //determine if nodes are in graph
        if(!contains_dict(src, vertsToInds) || !contains_dict(dest, vertsToInds)){
            return false;
        }
        //find relevant index for verticies
        size_t indexSrc = vertsToInds.at(src); //need to guarantee const for this to compile without errors
        size_t indexDest = vertsToInds.at(dest);
        //determine if edge already exists
        if(Morpheus[indexSrc][indexDest] == 0){
            return false;
        }
        return true;
    }
    double cost(size_t src, size_t dest) const{
        //make sure edge exists
        if(contains_edge(src,dest)){
            //simply return value stored in adjacency matrix
            size_t indexSrc = vertsToInds.at(src);
            size_t indexDest = vertsToInds.at(dest);
            return static_cast<double>(Morpheus[indexSrc][indexDest]);
        }
        else{
            //cost is infinite, because path doesn't exist
            return INFINITY;
        }
    }
    bool add_vertex(size_t id){
        //don't want to add multiple indexes with same id, so check that
        if(contains_dict(id, vertsToInds)){
            return false;
        }
        //add vertex to mapping of vertex to indicie
        vertsToInds[id] = nextInd;
        indsToVerts[nextInd] = id;
        nextInd++;
        //append zero to end of list
        for (int i = 0; i < vertexCount; i++){
            Morpheus[i].push_back(0);
        }
        //add new row for new vertex
        std::vector<size_t> tempVec;
        for (int j = 0; j < vertexCount+1; j++) {
            tempVec.push_back(0);
        }
        Morpheus.push_back(tempVec);
        //increase vertex cound
        vertexCount++;

        return true;
    }
    bool add_edge(size_t src, size_t dest, double weight=1){
        //determine if nodes are in graph
        if(!contains_dict(src, vertsToInds) || !contains_dict(dest, vertsToInds)){
            return false;
        }
        //find relevant index for verticies
        size_t indexSrc = vertsToInds[src];
        size_t indexDest = vertsToInds[dest];
        //determine if edge already exists
        if(Morpheus[indexSrc][indexDest] != 0){
            return false;
        }
        //add edge
        Morpheus[indexSrc][indexDest] = weight;
        edgeCount++;
        return true;
    }
    bool remove_vertex(size_t id){
        //determine if vertex exists
        if(!contains_dict(id, vertsToInds)){
            return false;
        }
        //find index of vertex
        size_t indexId = vertsToInds[id];
        //re-adjust indexes of elements after erased vertex (index = index-1)
        for(int i = indexId+1; i < vertexCount; i++){
            vertsToInds[indsToVerts[i]] -= 1;
            size_t temp = indsToVerts[i];
            indsToVerts.erase(i);
            indsToVerts[i-1] = temp;
        }
        //erase the final the column corresponding to removed vertex
        //we also need to count the number of edges it had, so we can remove them from overall count
        size_t temp_edge_count;
        for (int i = 0; i < vertexCount; i++){
        	if(Morpheus[i][indexId]!=0){
        		temp_edge_count++;
        	}
            //Morpheus[i].erase(Morpheus[i].begin() + indexId);
        }
        //erase vertex row
        //Morpheus.erase(Morpheus.begin() + indexId);
        //remove vertex from mapping
        vertsToInds.erase(id);
        indsToVerts.erase(indexId);
        nextInd--;
        vertexCount--;
        edgeCount-=temp_edge_count;
        return true;
    }
    bool remove_edge(size_t src, size_t dest){
        //determine if nodes are in graph
        if(!contains_dict(src, vertsToInds) || !contains_dict(dest, vertsToInds)){
            return false;
        }
        //find relevant index for verticies
        size_t indexSrc = vertsToInds[src];
        size_t indexDest = vertsToInds[dest];
        //determine if edge already exists
        if(Morpheus[indexSrc][indexDest] == 0){
            return false;
        }
        //remove edge
        Morpheus[indexSrc][indexDest] = 0;
        edgeCount--;
        return true;
    }


    // ** now for djikstra's, baby **
    int min_distance(std::unordered_map<size_t, size_t>dist, std::unordered_map<size_t, bool> nodesVisited){
        // Initialize min to check and the minimum index to return
        int min = INFINITY;
        int min_index;
        //find smallest edge to unvisited node
        for (int v = 0; v < vertexCount; v++){
            if (nodesVisited[v] == false && dist[v] <= min){
                min = dist[v];
                min_index = v;
            }
          }
          //return edge number
        return min_index;
    }
    void print_matrix(){
    	for (int x = 0; x < Morpheus.size(); x++) {
    		//std::cout << indsToVerts.at(x);
		    for (int y = 0; y < Morpheus[x].size(); y++){
				std::cout << Morpheus[x][y] << " ";
			}
		std::cout << std::endl;
   		}
    }
    void dijkstra(size_t source_id){
        //this unordered map will hold wether we have visited a node or not
        std::unordered_map<size_t, bool> nodesVisited;
        //make it so that we have not visited any nodes yet, path lengths to infinity
        for (int i = 1; i < vertexCount; i++){
            nodesVisited[i] = false;
            djikstraData[i] = INFINITY;
        }
        //source to self is zero
        size_t index_source_id = vertsToInds[source_id];
        djikstraData[index_source_id] = 0;
        //add path to djikstraPaths
        std::vector<size_t> tempVec;
        tempVec.push_back(source_id);
        djikstraPaths.push_back(tempVec);
        //parent[0] = -1;
        //iterate over all vertcies
        tempVec.clear();
        for(int i = 0; i < vertexCount - 1; i++) {
            //find min distance of unvisited nodes from current node
            int minty = min_distance(djikstraData, nodesVisited);
            
            //picked node is now visited
            nodesVisited[minty] = true;
            //distance to adjacent nodes may need to be updated
            for (int v = 0; v < vertexCount; v++){
                  //update node at v only if:
                  //it is not visited yet
                  //path to it doesn't equal zero
                  //it is reachable in djikstra list
                  //the value of the current distance and the distance of path from current node is less than current edge length.
                if (!nodesVisited[v] && Morpheus[minty][v] != 0 && djikstraData[minty] != INFINITY && djikstraData[minty] + Morpheus[minty][v] < djikstraData[v]){
                    djikstraData[v] = djikstraData[minty] + Morpheus[minty][v];
                    //tempVec.push_back(v);
                    //parent[v] = minty;
                }
            }
            //djikstraPaths.push_back(tempVec);
        }
    }
    double distance(size_t id) const{
        //if the value is in Djikstra Data, then return it, as it is it's minimum distance according to Djikstra's algorithm
        try{
            return djikstraData.at(vertsToInds.at(id));
        }
        catch(...){
            //if value wasn't in Djiksta Data, then a path to it doesnt exist, so should return infinity
            return INFINITY;
        }
    }
    void print_shortest_path(size_t dest_id, std::ostream& os=std::cout) const{
        
        try{
            //if the node travels to itself (ie, was the root node in djikstra's algorithm call), return itself and 0 distance
            if(djikstraData.at(dest_id) == 0){
                std::cout << dest_id << " distance: 0" << "\n";
            }
            else{
                for(int i = djikstraPaths.size()-1; i >= 0; i--){
                    if(djikstraPaths[i].back() == dest_id){
                        for(int j = 0; j < djikstraPaths[i].size()-1; j++){
                            std::cout << djikstraPaths[i][j] << " --> ";
                        }
                        std::cout << djikstraPaths[i][djikstraPaths[i].size()-1];
                        std::cout << " distance: " << djikstraData.at(vertsToInds.at(dest_id)) << "\n";
                    }
                }
            }
        }
        catch(...){
            //if value wasn't in Djiksta Data, then a path to it doesnt exist, so should print "<no path>\n"
            std::cout << "<no path>\n";
        }
    }

};

#endif  // GRAPH_H
