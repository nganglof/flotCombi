# flotCombi

Problème TSP : heuristique ClosestInsertion, DecreasingArc et FurthestInsertion
pour compiler : make
pour lancer le programme : ./main <methode> <instance>
methode 1 = ClosestInsertion
methode 2 = DecreasingArc
methode 3 = FurthestInsertion

ex: ./main 2 data/toy_instances/toy05.tsp pour lancer DecreasingArc sur l'instance toy05.tsp

Les résultats sont sous la forme :
DecreasingArc
	Nodes number : 5
	Path : 1,4,2,1,3,0
	Total distance : 407
	Algorithme executé en 177ms


Problème CVRP : heuristique ClarkeWright et GiantTour
pour compiler : exécuter d'abord le make du TSP, puis celui du CVRP (GiantTour nécessite les méthodes TSP pour fonctionner)
pour lancer le programme : ./main <methode> <instance> >methodeTSP dans le cas de GiantTour>

ex: ./main 2 Christophides_Eilon/E-n7.vrp pour lancer GiantTour sur l'instance E-07.vrp

Les résultats sont sous la forme : 
Christophides_Eilon/E-n7.vrp avec FurthestInsertion
Tours : 3 tournées
Tour #1 de distance 40 : 1 5 
Tour #2 de distance 42 : 2 3 6 
Tour #3 de distance 24 : 4 
pour une distance totale de 106, en 286ms
