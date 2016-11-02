void bestComercialRoute(Graph *Network, int destiny_id){
	
	Node *path;
	
	path = (Node*)malloc(sizeof(Node)*(Network->V))
	
	Disjkstra(Network, path, destiny_id);
	
	for(i=0; i < Network->V; i++){
		printf("path for %d isp is /n");
		for(j=path[i].v; path[j].v != destiny; j=path[j].v){
			printf("next hop = %d ", path[j].v);
		}
	}
}

void Disjkstra(Graph *Network, Node *path, int destiny_id){
	int *verify;
	Node *a;
	
	verify = (int*)malloc((Network->V)*sizeof(int));
	
	path[destiny_id].v = destiny_id;
	path[destiny_id].t = 3;
	path[destiny_id].nhops = 0;
	
	addToHeap(H, path[destiny_id]);
	
	for(i=0; HeapEmpty(H); i++){
		a = RemoveFromHeap(H);
		verify[a.v] = 1;
		for(aux = Network[a.v]->next;aux->next != NULL; aux=aux->next){
			if(verify[aux->v] == 0){
				if(Modeling(aux->t, a.t) > path[aux->v].t){
					path[aux->v].v = a.v;
					path[aux->v].t = Modeling(aux->t, a.t);
					path[aux->v].nhops = (path[a.v].nhops) + 1;
					addToHeap(H, path[aux->v]);
				}else if(Modeling(aux->t, a.t) = path[aux->v].t && ((path[a.v].nhops) + 1) < path[aux->v].nhops){
					path[aux->v].v = a.v;
					path[aux->v].nhops = (path[a.v].nhops) + 1;
					addToHeap(H, path[aux->v]);
				}
			}
		}
	}
}

int Modeling(int A, int a){
	switch(A) {
	   case 3  :
		  switch(a) {
			  case 3  :
				return 3;
				
			  default :
			  return 0;
		  }
		
	   case 2  :
		  switch(a) {
			  case 3  :
				return 2;
				
			  default :
			  return 0;
		  }
	  
	  case 1  :
		  switch(a) {
			  case 0  :
				return 0;
				
			  default :
			  return 1;
		  }
	}
}
