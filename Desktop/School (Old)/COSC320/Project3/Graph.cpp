
using namespace std;

#define RESET   "\033[0m"
// #define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
// #define WHITE   "\033[37m"      /* White */
// #define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
// #define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


map <int , string> colorNames; // map for terminal colors - used for printing node colors 



template <class T>
void printVector_set( vector<vector<T>> set){
    
    for(auto it : set){
        cout<<"{";

        for(T K:it ){
            cout<<K;
            
        }
        cout<<"}"<<endl;


    }

}


template <class T>
void printVector( vector<T> set){
        cout<<"{";
    
    for(auto it : set){

         cout<<it;
    }
        cout<<"}"<<endl;


}





template <class T>
Graph<T>::Graph(){

    // // initalizes a global bap variable "colorList" to be used to print terminal colors in functions 
    // string arr[12] = { RED,GREEN, YELLOW,BLUE,MAGENTA,CYAN, BOLDRED,BOLDGREEN,BOLDYELLOW,BOLDBLUE, BOLDMAGENTA,BOLDCYAN };
    //  for(int i =0; i< 12;i++){
    //     colorNames.emplace(i, arr[i] );
    // }

}



template <class T>
void Graph <T>::addVertex(T vertex){
 
    //TODO: copy and paste this into your lab 11

    for (auto it = vertices.begin(); it != vertices.end(); it++) {
        // if vertex is found
        if (it->first == vertex) {
			
            std::cout << RED << "Vertex " << vertex << " is already in the graph." << RESET << std::endl;
            return; // leave
        }
    }



    // inserts that node value with no neighbors ( empty vector)
    vertices.emplace(vertex, vector<T>());
}

// // add an undirected edge to the graph so add to both adjacency lists 
template <class T>
void Graph<T>::addEdge(T vertex, T vertex2 ){
    bool isPath1 = false, isPath2= false ; 
    for( auto it = vertices.begin(); it != vertices.end(); it++){

        if(it-> first == vertex){
            // searches through the list of neighbor nodes
            for( int i = 0; i < it->second.size() ;i++){
                if(it ->second[i] == vertex2){
                    isPath1= true;
                }
            }

            if(!isPath1){
                it->second.push_back(vertex2);
            }
        }

         // if the graph is undirected then add an edge 
        if(it-> first == vertex2 ){
            for( int i = 0; i < it->second.size() ;i++){
                // cout<<it->second[i]<<endl;
                if(it ->second[i] == vertex){
                    isPath1= true;
                }
            }

            if( isPath1 == false && isPath2 == false ){
                it->second.push_back(vertex);
            }
        }
    }
}


// // prints the adjacency list of each vertex, to show the structure
template <class T>
void Graph<T>::print(){

    if(vertices.size() ==0){
        cout<<"EMPTY GRAPH"<<endl;
    }
    for( auto it = vertices.begin(); it != vertices.end(); it++){
        cout<<"V= "<<it->first;
        cout<<" {";

        for( int i = 0; i < it->second.size() ;i++){
            cout<<it->second[i] <<", ";
        }
        cout<<"}"<<endl;
    }

}  

// GreedyColoring(Graph G(V, E)):
// 	for all v ∈ V(G):
// 		color(v) ←  -1
// 	for all v ∈ V(G) in order:
// 		isColored (1… ∆(G) + 1) ← false // initiaizing SOMETHING to false for every vertex in the graph 
// 		for all u ∈ N(v) where color(u) ≠ −1 // for all neighbors where it is marked 
// 			isColored (color(u))  ← true // if is colored then indicate it 
// 		for k = 1… ∆(G) + 1: 
// 			if isColored (k) = false:
// 				color(v) ← k
// 				break
// 	k ← max(color(1...n))
// // return k // returns the number of colors used 

template <class T>
void  Graph<T>::greedyColor(){
    auto it = vertices.begin();
    greedyColor(it->first);

}


template <class T>
void  Graph<T>::greedyColor(T vertex){
    map< T , int > coloredGraph; // stores the final colored graph
    list <int> totalColors;
    int color = 1 ;

    for(  T i : vertices[vertex]){
        coloredGraph.emplace(i, -1);
    }

    for( auto it = vertices.begin(); it != vertices.end(); it++){
        list <int> availableColors = totalColors; // use overloaded = to copy all of the colors in the graph is later modified 

        for( auto j = 0; j < it->second.size() ;j++){

             //for every colored neighbor of u 
            if(coloredGraph[it->second[j]] > 0 ){ 
                // for every colored neighbor take out that color from the availableColors list 
                availableColors.remove(coloredGraph[it->second[j]]);

            }
            
            // current "hub" uses all available colors... assign current node to a new color 
            if(availableColors.empty()){
                totalColors.push_front(color); // add color to our list of colors
                coloredGraph[it->first] = color;
                color++;

            // there exists an available color to assign the current node to... i.e select from beg of list 
            }else{ 
                int color = availableColors.front();
                coloredGraph[it->first] = color;

             }
        }
    }

    printf("\n\nFINAL COLORING\n");

    for( auto i = vertices.begin(); i != vertices.end(); i++){
        int color = coloredGraph[i->first];
        cout<<"node=" <<i->first <<" color= " << colorNames[color]<< coloredGraph[i->first] <<RESET<<endl;
    }
    printf("There were %lu colors used to color the graph \n\n", totalColors.size());

}



// passing in a graph that needs the correct edges added but already has the verticies
template <class T>
Graph<T> Graph<T>::makeSubgraph( Graph  & newGraph, bool print){
    //cout<<"ENTER makeSubgraph"<<endl;


    // for every pair of verticies in new graph 
        // double for loop i , j 
        // see if the main graph has an edge between them
            // see if j is in i's adjacency list 
            // find(vertices[i].begin(),vertices[i].end(), j ) // start , end , target 

                    // will return to the it to the obj or the it to the end of the array 
                        // i.e test if find() == vertices[i].end()== end)

        if (print)
            cout<<"size="<<  newGraph.vertices.size()<<endl;
        
        for(auto it = newGraph.vertices.begin() ; it != newGraph.vertices.end() ; it++){
            T node1 = it->first;
            if (print)
                cout<<"node1"<<node1<<endl;

            // for(auto neighbor : it->second){
            for(auto it2 = newGraph.vertices.begin() ; it2 != newGraph.vertices.end() ; it2++){

                T node2 = it2->first;
                if (print)
                    cout<<"node1"<<node1<<" node2 "<<node2<<endl;

                auto isNode1 = find(vertices[node2].begin() , vertices[node2].end() , node1); // is node 1 in the neighborhood of node2 
                // auto isNode2 = find(vertices.begin() , vertices.end() , node2);
                if(isNode1 != vertices[node2].end() ){
                    newGraph.addEdge(node1,node2);
                }

            }



        }







    // it thru verticies, if the verticies math then add all of the neighbors 
    
    // auto graphIt = newGraph.vertices.begin();
    // for (auto it = vertices.begin(); it != vertices.end(); it++) {
    // //     // if vertex is found and iterate thru neighbors... add edges 
    //         cout<<"MATCH original node= "<<it ->first<<" new Node="<<graphIt->first<<endl;

    //     if(graphIt != newGraph.vertices.end()){
    //         //  graphIt++;
    //         // cout<<"original node= "<<it ->first<<" new Node="<<graphIt->first<<endl;
        
    //         if (it->first == graphIt->first) {
    //         // cout<<"MATCH original node= "<<it ->first<<" new Node="<<graphIt->first<<endl;

    //             cout<<"MATCH"<<endl;
    //             T node1 = it->first;

    //             for( auto i : vertices [it->first]){
    //                 T node2 = i;

    //                 if( newGraph.vertices.count(i) > 0){ // both nodes exist in the newGraph and the edges between them need to be added 
    //                     newGraph.addEdge(node1 , node2);
    //                 }
    //             }
            
    //         }
    //     }
    //     if(graphIt != newGraph.vertices.end()){
    //         //  graphIt++;

    //     }

    // }


    // newGraph.print();
    return newGraph;

}


// pass in 2^n and the graph array to generate all SUBGRAPHS
template <class T>
map<string, Graph<T>> Graph<T>:: genSubgraphs(){

    int n = pow(2, vertices.size() ); /* 2**vetices.size */
    int totalBits =log2(n);
    // cout<<"n="<<n<<endl;
    // cout<<"totalBits"<<totalBits<<endl;
    // int bitNum = 1;
    int arrIndex = 0 ;

    // the lhs is a binary string, e.g. "001001011" that maps to 
    // the corresponding subgraph
    map <string,Graph<T>> subGraphs;

    queue<string> qu;
    qu.push("1");
    while(n != 0 ){

        string s1 = qu.front();
        // cout<<"STRING"<<s1 <<endl;

        qu.pop();

        // if( ceil(log2(qu.size()+1)) == floor(log2(qu.size()+1)) ){
        //     bitNum ++;
        // }
     
        
        Graph <T> temp;   
        string bitStr = s1;
        while(bitStr.length() < totalBits){
            bitStr = "0" + bitStr;
        }


        auto it = vertices.begin(); 
        for(int i =0; i < vertices.size()  ;i++){

            if(bitStr[i] =='1' ){
                temp.addVertex(it->first);
            }
            if(it != vertices.end()){
                it++;
            }

        }
        
        //arr[arrIndex] = temp;
        //rtn.push_back(temp);

        if(bitStr.size() == totalBits){
            subGraphs.emplace(bitStr, makeSubgraph(temp, false));

        }

        // subGraphs[bitStr] = temp;
        

        // cout<<endl;
        // arrIndex++;

        string s2 = s1;
        qu.push(s1 + "0");
        qu.push(s1 + "1");
        n--;
    }




    // cout <<"final"<<endl;

    // int i =0;
    // for(auto it = subGraphs.begin() ;it != subGraphs.end() ;  it++){
    //     cout<<i++<<endl;
    //     cout<<"str" << it->first<<endl;
    //     it->second.print();

    //     cout<<endl;
    // }

    return subGraphs;

}


// given a graph and a vertex will return the degree 
template <class T>
int Graph<T>::degree(Graph current, T vertex){

    // todo: double check 
     if(current.vertices.size() ==0){
        // cout<<"base case"<<endl;

        return 0;
    }

    for (auto it = current.vertices.begin(); it != current.vertices.end(); it++) {
       if(it->first == vertex){
           cout<<it->second.size()<<endl;
           return it->second.size();

       }
    }
   
    return -1;
}


// finds first instance for the smallMis graph 
// template <class T>
// degreePair<T>  Graph<T>::findDegree(Graph current){
//     degreePair <T> set;
//     int index=0;
//     for (auto it = current.vertices.begin(); it != current.vertices.end(); it++ ,index++) {
//         int degreeNum = degree( current , it->first) ;

//         if( degreeNum>= 3 || degreeNum== 1 || degreeNum== 0){
//             set.vertexValue = it->first;
//             set.degree= degreeNum;
//         }
//     } 

//     return set; // there is not a case that satsifies the the first if statements in smallMIS 
// }


template <class T>
vector <T> Graph<T>::setUnion( vector <T> set1 , vector<T>  set2){
    // cout<<"here1:"<<endl;
    vector<T> v( set1.size() +set2.size());  

    auto it= set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), v.begin());
    v.resize(it-v.begin());   

    return v;  
}

template <class T>
vector <T> Graph<T>::symDiff( vector <T> set1 , vector<T>  set2){
    vector<T> v( set1.size() +set2.size()  );  
    auto it =  set_symmetric_difference (set1.begin(), set1.end(), set2.begin(), set2.end(), v.begin());
    v.resize(it-v.begin());   

    return v;   
}


// given a graph and two nodes are the two nodes ever connected i.e neighbors 
template <class T>
bool Graph<T>::areConnected(Graph subGraph, T node1 , T node2){
    for(auto i : subGraph.vertices [node1]){
            // cout<< "i= "<<i <<" node1 = "<<node1 <<" node2="<<node2<<endl;
        if(i == node2){
            // cout<<"correct neighbor"<<endl;
            return true;

        }        

    }
    // cout<<"NOT neighbor"<<endl;
    return false;   
}


// find all independet sets and then keep the "largest ones" and return for the color function to iterate 

template <class T>
vector< vector<T> > Graph<T>::checkIndependentSets(Graph subGraph, vector< vector<T>> currentSet){
    vector< vector<T>> indep_Sets ;
    // cout<<"checkIndependentSets"<<endl;
    // printVector_set(currentSet);

    int maxSizeMIS =0;

    // checks if there are two adjacent edges 
    // iterate thru the sets of current sets 
    for(auto i : currentSet){
        bool addList = true;

        for(T node1:i ){
            for(T node2:i ){
                if(areConnected(subGraph , node1 , node2) == true){ // tests to see if two neighbors are adjacent
                    addList = false; // the first instance that it is stops looking at this set 
                    break;
                }
            }

        }

        //measures the max Size of the independent set
        if(addList == true  ){
            // indep_Sets.push_back(i);
            if(i.size() > maxSizeMIS){
                maxSizeMIS = i.size();
            }
        }

    }



    // does the whole thing again but only adds the sets of the largest maxsize to return 
    for(auto i : currentSet){
        bool addList = true;

        for(T node1:i ){
            for(T node2:i ){
                if(areConnected(subGraph , node1 , node2) == true){
                    addList = false;
                    break;
                }
            }

        }
        if(addList == true  &&  i.size() == maxSizeMIS){
            indep_Sets.push_back(i);
           
        }

    }

    return indep_Sets;

}



// gen sets given a vector of verticies 
template <class T>
void Graph<T>:: genSets(int n , vector<vector<T>> & sets){
    int totalBits =log2(n);
    int bitNum = 1;
    int arrIndex =0;

    queue<string> qu;
    qu.push("1");
    while(n != 0){
        string s1 = qu.front();
        qu.pop();

        if( ceil(log2(qu.size()+1)) == floor(log2(qu.size()+1)) ){
            bitNum ++;
        }
     

        vector <T> temp;   
        string bitStr = s1;
        while(bitStr.length() < totalBits){
            bitStr = "0" + bitStr;
        }

        auto it = vertices.begin(); 
        // cout <<"\nhere"<< bitStr<<endl;
        for(int i =0; i < vertices.size()  ;i++){
            if(it != vertices.end()){

                if(bitStr[i] =='1' ){
                    temp.push_back(it->first);
                }
            }

            if(it != vertices.end()){
                it++;


            }

        }
        
        
        sets.push_back(temp);


        string s2 = s1;
        qu.push(s1 + "0");
        qu.push(s1 + "1");
        n--;
    }



}

//given a graph: will return all verticies in the set
template <class T>
vector<T> Graph<T>:: get_verticesSet(Graph current){
    vector <T> S;

    for (auto it = current.vertices.begin(); it != current.vertices.end(); it++) {
        S.push_back(it->first);
    }
    return S;

}


// given a vector with verticies, will determine its binary representation 
template <class T>
string Graph<T>:: get_binary(vector<T> current){
    string bin;

    for(int i =0;i< vertices.size() ;i++){ // need all the verticies in the calling graph for chrom number
        bin+="0";
    } 

    int index =0;
    for(auto i=vertices.begin(); i != vertices.end()  ;i++ ){
        // cout<<"index"<<index<<endl;
        for(auto vertex : current){ // iterate on all verticies in the current graph to see if also in original graph

            if(vertex == i ->first){
                bin[index] = '1';
                // cout<<"vertex "<<vertex <<" "<<i->first<< " "<< endl;
                // cout<<"index"<<index<<endl;
            }
        }
        index++;
    } 
    
    index--;
    int binaryNum =0;
    // cout<<"binary string"<<bin<<endl;
    for(int i = 0 ; i<vertices.size() ;i++){
        if(bin[i] == '1'){
            binaryNum += pow(2, index );
        }
        index--;

    }

    // cout<<"Str = "<< bin << " binary number is "<<binaryNum<<endl;
    // return to_string(binaryNum);

    return bin;
}

// takes info from a given graph (will be a subgraph) and sends the info to SMALL MIS in the correct format
template <class T>
void Graph<T>::prepMIS(Graph current ,  vector <vector<T>> & set_MIS){
 
    // current.print();


    // 2^n set of verticies and go through and make sure they are not connected by an edge 
    int graphSize = pow(2,current.vertices.size());
    current.genSets( graphSize, set_MIS);
    


    // cout<<"printing the gen sets"<<endl;
    // printVector_set(set_MIS);

    // // 3. weed out non-independent sets and return the valid ones 
    set_MIS = checkIndependentSets(current ,  set_MIS);

    // cout<<"printing the weed out gen sets"<<endl;
    // printVector_set(set_MIS);
    


     
// 2. generate 2^n  sets of verticies  
// 3. Check if independent set ... aka set DN have two adjacent verticies 
// - do them all first . Find Max then add all those to the set 
// - keep track of all the “maximum” size of each independent set … 

// - iterate in the for loop for this line  X[S] = min(X[S], X[S \ I] + 1) 


// smallMIS(current, set_MIS, S , I , S.size()-1  );
// find all independet sets and then keep the "largest ones" and return for the color function to iterate 
    

}

template <class T>
string Graph<T>::binValue(int ){

}


template <class T>
void Graph<T>::color(bool print){

    int arrSize = pow(2, vertices.size());
    map<string, Graph<T>> subGraphs = genSubgraphs();
    map<string, int > X ;

    X.emplace("0000",0);
    for(auto S =subGraphs.begin() ; S !=subGraphs.end() ; S++){

        if(S->second.vertices.size() ==1 ){
            X.emplace(S->first, 1 );

        }else{
            X.emplace(S->first, arrSize );

        }


    }

    if (print)
        cout<<"printing X"<<endl;
    
    if (print) {
        for(auto S =X.begin() ; S !=X.end() ; S++){
            cout<<S->first <<"= "<<S->second<<endl;
        }
    }
    
    if (print) {
        cout<<"size X"<< X.size()<<endl;
        cout<<"size X"<< subGraphs.size()<<endl;
    }


    for(auto S =subGraphs.begin() ; S !=subGraphs.end() ; S++){
        // call prepMIS on every graph which generates all information for independet sets
        
        vector <vector<T> > MIS;
        if (print) {
            cout<<"printing subgraph"<<endl;
            S->second.print();
        }
        // cout<<endl;

        prepMIS(S->second , MIS); // populate MIS with maximal independent sets of G[S]

        if (print) {
            cout<<"PRINTING"<<endl;
            printVector_set(MIS);
            cout<<endl;
        }
        // for every maximum independent set found from this subgraph
        for(auto vectorIT : MIS){

                // vector<T> S_I = get_verticesSet(subGraphs[S]); 
                vector<T> S_I = get_verticesSet(S->second); 
                if (print) {
                    cout<<"BEFORE SYM DIFF"<<endl;
                    printVector(S_I);
                }

                S_I = symDiff(S_I, vectorIT);
                // get_binary(S_I);
                if (print) {
                    cout<<"PRINTING VECTOR FOR the binary"<<endl;
                    printVector(S_I);
                    printVector(vectorIT);
                }

                if (print)
                    cout<<X[S->first] <<" VS  "<<  X[ get_binary(S_I)] +1<<endl;

                X[S->first] = min( X[S->first] , X[ get_binary(S_I)] +1 );

                if (print) {
                    cout<<"PRINTING S values"<<endl;
                    cout<<"index= " <<S->first <<" chromatic number assigned "<<X[S->first]<<endl;
                    cout<<endl;
                }
               

                 // psuedocode
                // X[S] = min(X[S], X[S \ I] + 1

        }


    }

      
    // for(auto S =X.begin() ; S !=X.end() ; S++){
    //     cout<<S->first <<"= "<<S->second<<endl;

    // }

    auto it = X.crbegin();
    it++;
    cout<<"The chromatic number of the graph is "<< it->second<<endl;


}




