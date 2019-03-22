#include "Graph.h"
#include "GraphAlgo.h"
#include "GraphWriter.h"
#include "gtest/gtest.h"
using namespace std;
using ::testing::InitGoogleTest;
using ::testing::Test;

int main(int argc, char **argv) {
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(GraphAlgo, IsConnected) 
{
	CGraph pGraph(GraphType::UnDirected);
	pGraph.AddNodes({ {0, "Node0"}, {1, "Node1"}, {2, "Node2" }, {3, "Node3"}, {4, "Node4"} });
	pGraph.AddEdges({ {0, 1, 1 }, {0, 2, 1 }, {1, 2, 1}, {3, 4, 1} });

	CGraphAlgo pAlgo(&pGraph);
	ASSERT_TRUE(pAlgo.IsConnected(0, 1, SearchAlgo::BFS));
	ASSERT_TRUE(pAlgo.IsConnected(0, 1, SearchAlgo::DFS));
	
	ASSERT_FALSE(pAlgo.IsConnected(0, 4, SearchAlgo::BFS));
	ASSERT_FALSE(pAlgo.IsConnected(0, 4, SearchAlgo::DFS));
}

TEST(Graph, Visualize)
{
	CGraph pGraph(GraphType::UnDirected);
	pGraph.AddNodes({ {0, "Node0"}, {1, "Node1"}, {2, "Node2" }, {3, "Node3"}, {4, "Node4"} });
	pGraph.AddEdges({ {0, 1, 1 }, {0, 2, 1 }, {1, 2, 1}, {3, 4, 1} });

    CGraphWriter pWriter(pGraph);
	pWriter.Visualize();
}

TEST(GraphAlgo, Djikstra)
{
	CGraph pGraph(GraphType::UnDirected);
	pGraph.AddNodes({ {0, "Node0"}, {1, "Node1"}, {2, "Node2" }, {3, "Node3"}, {4, "Node4"} });
	pGraph.AddEdges({ { 0, 1, 1 }, { 0, 2, 4 }, { 1, 2, 1 }, { 3, 4, 3 } });

	CGraphAlgo pAlgo(&pGraph);
	map<int, int> ShortestPaths = pAlgo.Djikstra(0);

	EXPECT_EQ(ShortestPaths.size(), 5);
	EXPECT_EQ(ShortestPaths.at(0),  0);
	EXPECT_EQ(ShortestPaths.at(1),  1);
	EXPECT_EQ(ShortestPaths.at(2),  2);
	EXPECT_EQ(ShortestPaths.at(3),  INF);
	EXPECT_EQ(ShortestPaths.at(4),  INF);
}
