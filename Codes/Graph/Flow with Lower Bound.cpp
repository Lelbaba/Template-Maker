///flow with demand(lower bound) only for DAG
//create new src and sink
//add_edge(new src, u, sum(in_demand[u]))
//add_edge(u, new sink, sum(out_demand[u]))
//add_edge(old sink, old src, inf)
// if (sum of lower bound == flow) then demand satisfied
//flow in every edge i = demand[i] + e.flow
