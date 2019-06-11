#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"
#include <bits/stdc++.h> 

using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();

//Check for Solvability (Done!!)
//NN is redundant!!!
vector<pair<string, int>> imbalanced_nodes() 
{
    //Store all nodes
    Vertex *a = nm->get_all_nodes();
    vector <string> NN;
        while (a!= NULL) {
            NN.push_back(a->name);
            a = a->next;
        }    
    //for(int i = 0; i < NN.size(); ++i)
        //cout << NN.at(i) << endl;
    
    vector<pair<string, int>> all_degree(NN.size());  //string(node_name), int(vertex_degree) 
    Edge *e = nm-> elist;
    
    for (int i = 0; i < NN.size(); i++) {
        all_degree.at(i).first = NN.at(i);
        while (e!= NULL) {
            if (NN.at(i) == e-> head-> name)        
                all_degree.at(i).second = all_degree.at(i).second+ 1;
            else if (NN.at(i) == e-> tail-> name)   
                all_degree.at(i).second = all_degree.at(i).second- 1;
            else if ((NN.at(i) == e-> head-> name) && (NN.at(i) == e-> tail-> name))    
                all_degree.at(i).second = all_degree.at(i).second;
            else                                    
                all_degree.at(i).second = all_degree.at(i).second;
            e = e-> next;            
        }
        e = nm-> elist;
    }
    cout << "\nCheck for Solvability: " << endl;
    for(int i = 0; i < NN.size(); i++)
        cout << NN.at(i) << ": " << all_degree.at(i).second << endl;
    
    return all_degree;
}
    

//Find imbalanced nodes
vector<pair<string, int>> find_nonzero_nodes (const vector<pair<string, int>> &_all_degree) 
{
    vector<pair<string, int>> nonzero_nodes;
    
    //cout << _all_degree.size();
    for (int i = 0; i< _all_degree.size(); i++) {
        if (_all_degree.at(i).second != 0)
            nonzero_nodes.push_back(_all_degree.at(i));
    }
    /*
    cout << "nonzero_nodes: ";
    for(int i = 0; i < nonzero_nodes.size(); i++) {
        cout << nonzero_nodes.at(i).first;
    }
    cout << endl;
    */
    return nonzero_nodes;
}

vector<string> positive_degree (const vector<pair<string, int>> &_find_nonzero_nodes) 
{
    vector<string> positive_degree;
    for (int i = 0; i< _find_nonzero_nodes.size(); i++) {
        if (_find_nonzero_nodes.at(i).second > 0)
            positive_degree.push_back(_find_nonzero_nodes.at(i).first);
    }
    /*
    cout << "pos: ";
    for(int j = 0; j < positive_degree.size(); j++) {
        cout << positive_degree.at(j);
    } 
    cout << endl;
    */
    return positive_degree;
}

vector<string> negative_degree (const vector<pair<string, int>> &_find_nonzero_nodes) 
{
    vector<string> negative_degree;
    for (int i = 0; i< _find_nonzero_nodes.size(); i++) {
        if (_find_nonzero_nodes.at(i).second < 0)
            negative_degree.push_back(_find_nonzero_nodes.at(i).first);
    }
    
    cout << "neg: ";
    for(int i = 0; i < negative_degree.size(); i++) {
        cout << negative_degree.at(i);
    }
    cout << endl;
    
    return negative_degree;
}

//vector<int> length (Path *path)
int min_length (Path *path) 
{
    vector<int> length(path-> paths.size());
    int min_length= 0;
    for(int i= 0; i< path-> paths.size(); i++) {
        for(int x= 0; x< path-> paths.at(i).size(); x++) {
            length.at(i) = length.at(i) + path-> paths.at(i).at(x)->flowval;
        }
    }
    min_length= *min_element(length.begin(), length.end());
    /*
    for (int i= 0; i < length.size(); i++) {
        cout << length.at(i) << endl;
    }*/
    cout << "min_length: " << min_length << endl;
    return min_length;
}

//permutation and make pair
void work_hard (const vector<string> &positive_degree, const vector<string> &negative_degree) {
    vector<vector<string> > _pair;
    
}
//Add additional paths
    
//Using gplot to export dotfile
    void draw (NetworkManager *draw) 
    {
        Gplot *gp = new Gplot();
        gp->gp_add(draw->elist);
        gp->gp_dump(true);
        gp->gp_export("plot");
    };
    
//Specifying the Euler Tour (Hierholzer algorithm)
void printCircuit(vector< vector<int> > adj) 
{ 
    // adj represents the adjacency list of 
    // the directed graph 
    // edge_count represents the number of edges 
    // emerging from a vertex 
    unordered_map<int,int> edge_count; 
  
    for (int i=0; i<adj.size(); i++) 
    { 
        //find the count of edges to keep track 
        //of unused edges 
        edge_count[i] = adj[i].size(); 
    } 
  
    if (!adj.size()) 
        return; //empty graph 
  
    // Maintain a stack to keep vertices 
    stack<int> curr_path; 
  
    // vector to store final circuit 
    vector<int> circuit; 
  
    // start from any vertex 
    curr_path.push(0); 
    int curr_v = 0; // Current vertex 
  
    while (!curr_path.empty()) 
    { 
        // If there's remaining edge 
        if (edge_count[curr_v]) 
        { 
            // Push the vertex 
            curr_path.push(curr_v); 
  
            // Find the next vertex using an edge 
            int next_v = adj[curr_v].back(); 
  
            // and remove that edge 
            edge_count[curr_v]--; 
            adj[curr_v].pop_back(); 
  
            // Move to next vertex 
            curr_v = next_v; 
        } 
  
        // back-track to find remaining circuit 
        else
        { 
            circuit.push_back(curr_v); 
  
            // Back-tracking 
            curr_v = curr_path.top(); 
            curr_path.pop(); 
        } 
    } 
  
    // we've got the circuit, now print it in reverse 
    cout<<"*****************************************************************************************************"<<endl;
    cout<<"Path:"<<endl;
    for (int i = circuit.size()-1; i>=0; i--) {  
        
        if(circuit[i]==0)  cout<<"a";
        if(circuit[i]==1)  cout<<"b";
        if(circuit[i]==2)  cout<<"c";
        if(circuit[i]==3)  cout<<"d";
        if(circuit[i]==4)  cout<<"e";
        if(circuit[i]==5)  cout<<"f";
        if(circuit[i]==6)  cout<<"g";
        if(circuit[i]==7)  cout<<"h";
        if(circuit[i]==8)  cout<<"i";
        if(circuit[i]==9)  cout<<"j";
        if(circuit[i]==10) cout<<"k";
        /*
        if(circuit[i]==0)  cout<<"0";
        if(circuit[i]==1)  cout<<"1";
        if(circuit[i]==2)  cout<<"2";
        if(circuit[i]==3)  cout<<"3";
        if(circuit[i]==4)  cout<<"4";
        if(circuit[i]==5)  cout<<"5";
        */
        if (i) 
           cout<<" -> "; 
    }
    cout<<endl;
}
    
int main(int argc, char** argv)
{ 
    nm->interpret("topo.txt");
    nm->print_all_e();
    //cout << endl;
    //nm->print_all_v();
    //vector<pair<string, int>> A = imbalanced_nodes();
    vector<pair<string, int>> K = find_nonzero_nodes(imbalanced_nodes());
    vector<string> _positive_degree = positive_degree(K);
    vector<string> _negative_degree = negative_degree(K);
    //int min_nth = min_nth(ans, pair_length);
    
    Path *path;
    path = new Path();
    path-> append(nm-> elist);
    //int _length = min_length(path);
    //work_hard(_positive_degree, _negative_degree);
    vector<vector<string> > _pair(_positive_degree.size());
    int cnt= 0;
    do {
        for (int i=0; i < _positive_degree.size(); i++) {
            //cout << _negative_degree.at(i) << " " <<  _positive_degree.at(i);
            //cout << endl;
            _pair.at(cnt).push_back(_negative_degree.at(i));
            _pair.at(cnt).push_back(_positive_degree.at(i));
        }
        cnt = cnt+ 1;
    }
    while (next_permutation(_positive_degree.begin(), _positive_degree.end()));
    /*
    if {
        for (int i=0; i < _positive_degree.size(); i++) {
            //cout << _negative_degree.at(i) << " " <<  _positive_degree.at(i);
            //cout << endl;
            _pair.at(cnt).push_back(_negative_degree.at(i));
            _pair.at(cnt).push_back(_positive_degree.at(i));
        }
        cnt = cnt+ 1;
    }
    while (prev_permutation(_positive_degree.begin(), _positive_degree.end()));
    */
    //cout << _pair[0].size() << endl;
    /*
    for (int i=0; i < _pair.size(); i++) {
            for (int j=0; j < _pair.at(i).size(); j++) {
                cout << _pair.at(i).at(j) << " ";   
            }
            cout << endl;
        }
    */
    //set pair length and minimize it
    int _pair_length= 0;  
    //int sht_pair_length= 0;
    int ans= 0;
    vector<int> pair_length;
    //vector<string> min_vec;
    string neg, pos;
    for (int i= 0; i< _pair.size(); i++) {
        //cout << i << endl;
        int sht_pair_length= 0;
        for (int j=0; j < _pair.at(i).size()/2; j++) {
            //cout << j << endl;
            neg = _pair.at(i).at(j* 2);
            pos = _pair.at(i).at(j* 2+ 1);
            path-> append(nm-> elist);
            path-> find_paths(neg, pos);
            //min_vec.push_back(neg);
            //min_vec.push_back(pos);
            cout << neg << " to " << pos << " ";
            _pair_length = min_length(path);
            sht_pair_length += _pair_length;    
        }
        //cout << "aaa" << endl;
        //cout << sht_pair_length << endl;
        pair_length.push_back(sht_pair_length);   
    }
    ans= *min_element(pair_length.begin(), pair_length.end());
    /*
    for (int i= 0; i< _pair.size(); i++) {
        for (int j=0; j < _pair.at(i).size()/2; j++) {
            cout << _pair.at(i).at(j* 2) << _pair.at(i).at(j* 2+ 1) << " ";
        } 
    }*/
    //cout << endl;
    /*for (int i= 0; i< pair_length.size(); i++) {
        cout << pair_length.at(i) << " ";
    }*/
    cout << "shortest pair length: " << ans << endl;
    cout << endl;
    
    //Add additional paths
    int min_nth= distance(pair_length.begin(), min_element(pair_length.begin(), pair_length.end()));
    //cout << min_nth << endl;
    string head, tail;
    for (int i= 0; i< _pair.at(min_nth).size()/2; i++) {
        //cout << i << endl;
        head = _pair.at(min_nth).at(i* 2);
        tail = _pair.at(min_nth).at(i* 2+ 1);
        path-> append(nm-> elist);
        path-> find_paths(head, tail);
        cout << head << " to " << tail << " ";
        cout << endl;
        vector<int> length(path-> paths.size());
        for(int i= 0; i< path-> paths.size(); i++) {
            for(int x= 0; x< path-> paths.at(i).size(); x++) {
                length.at(i) = length.at(i) + path-> paths.at(i).at(x)->flowval;
            }
        }
        int nth_paths= distance(length.begin(), min_element(length.begin(), length.end()));
        for(int x= 0; x< path->paths.at(nth_paths).size(); x++) {
            nm-> connect(path->paths.at(nth_paths).at(x)->head-> name, 
                        path->paths.at(nth_paths).at(x)->tail-> name);
        }
    }
    draw(nm);
    nm->print_all_e();
    Edge *_edge=nm->elist;
    int row=0;
    int col=0;
    vector<vector<int> > adj1(15); 
    while (_edge!=NULL) {
        _edge->head->name;
        
        if(_edge->head->name=="a") row=0;
        if(_edge->head->name=="b") row=1;
        if(_edge->head->name=="c") row=2;
        if(_edge->head->name=="d") row=3;
        if(_edge->head->name=="e") row=4;
        if(_edge->head->name=="f") row=5;
        if(_edge->head->name=="g") row=6;
        if(_edge->head->name=="h") row=7;
        if(_edge->head->name=="i") row=8;
        if(_edge->head->name=="j") row=9;
        if(_edge->head->name=="k") row=10;
        if(_edge->tail->name=="a") col=0;
        if(_edge->tail->name=="b") col=1;
        if(_edge->tail->name=="c") col=2;
        if(_edge->tail->name=="d") col=3;
        if(_edge->tail->name=="e") col=4;
        if(_edge->tail->name=="f") col=5;
        if(_edge->tail->name=="g") col=6;
        if(_edge->tail->name=="h") col=7;
        if(_edge->tail->name=="i") col=8;
        if(_edge->tail->name=="j") col=9;
        if(_edge->tail->name=="k") col=10;
        
        if(_edge->head->name=="0") row=0;
        if(_edge->head->name=="1") row=1;
        if(_edge->head->name=="2") row=2;
        if(_edge->head->name=="3") row=3;
        if(_edge->head->name=="4") row=4;
        if(_edge->head->name=="5") row=5;
        if(_edge->tail->name=="0") col=0;
        if(_edge->tail->name=="1") col=1;
        if(_edge->tail->name=="2") col=2;
        if(_edge->tail->name=="3") col=3;
        if(_edge->tail->name=="4") col=4;
        if(_edge->tail->name=="5") col=5;
        
        adj1.at(row).push_back(col);
        _edge = _edge->next;
    }
    printCircuit(adj1);
    
    //Calculate cost
    int _cost= 0;
    int Cost= 0;
    Edge *cost = nm->elist;
    while (cost!= NULL) {
        _cost += cost-> flowval;
        cost = cost->next;
    }
    Cost= _cost+ ans;
    cout << "\nCost:\n" << Cost;
    cout<<"\n*****************************************************************************************************"<<endl;
    cout << endl;
    return 0;
}