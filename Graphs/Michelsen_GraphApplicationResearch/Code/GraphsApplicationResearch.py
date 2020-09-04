# This file is the main file for my program. For this assignment, I decided to research 
# the NetworkX library for Python. In this file, I generate an undirected, weighted graph
# and process the graph algorithm using the following three algorithms: A*, Triangles, and
# PageRank. Each algorithm processes a different aspect of the graph. A* calculates the 
# shortest path between two nodes. Triangles is a clustering algorithm that detects the
# number of triangles between nodes (sets of three nodes that each have a relationship)
# to the others). Finally, PageRank is a link analysis algorithm that determines the
# importance of nodes in the graph based on all other nodes. 
# After processing the graph, it is displayed using two different formats: adjacency 
# list and edge list. The application also outputs the graph to an image. The program
# also outputs files containing data related to the graph (the adjacency list, edge)
# list, page rank, A* path, and triangle count).
#
# This application uses Python v. 3.7
# This application uses NetworkX v. 2.2
# This application uses 3.0.2
#
# Author: Brandon Michelsen

# Import necessary libraries
import networkx as nx # NetworkX, used for graph functions 
import matplotlib.pyplot as plt # matplotlib, used for outputting the graph
import os # Import OS functionality for display

# Create a function for running the Triangles algorithm
# Takes a parameter for the graph to run the algorithm on
def run_triangles(G):
	print("Counting the number of triangles in the graph...\n")
	triangles = nx.triangles(G) # Get the triangles count of the given graph
	print("Saving triangles data to file...\n")
	f = open("Output Text Files\Graph_Triangles.txt", "w") # File to save the triangles to
	# Write the result of the triangles algorithm to the file
	for key, val in triangles.items():
		f.write(str(key)+': '+str(val)+'\n')
	f.close() # Close the file
	print("Showing Triangles data:")
	# Print the triangles output to the screen
	for node, tri in triangles.items():
		print(str(node)+': '+str(tri))
	print()

# Create a function for running the A* algorithm
# Takes parameters for the graph to run the algorithm on
# and the starting and ending nodes
def run_astar(G, start, end):
	print("Generating shortest path...\n")
	shortest_path = nx.astar_path(G, start, end) # Run the A* algorithm on the given graph
	print("Saving path to the output file...\n")
	f = open("Output Text Files\Graph_AStar.txt", "w") # File to save the A* path to
	# Write the A* path to the file
	for node in shortest_path:
		f.write(str(node)+'\n')
	f.close() # Close the file
	print("Showing the path:")
	# Print the A* output to the screen
	for node in shortest_path:
		print(node, sep=' -> ')
	print()

# Create function for running the PageRank algorithm
# Takes a parameter for the graph to run the algorithm on
def run_pagerank(G):
	print("Generating PageRank data...\n")
	page_rank = nx.pagerank(G, alpha=0.9) # Run the PageRank algorithm
	print("Saving data to output file...\n")
	f = open("Output Text Files\Graph_PageRank.txt", "w") # File to save the PageRank data to
	# Write the PageRank data to the file
	for key,val in page_rank.items():
		f.write(str(key)+': '+str(val)+' \n')
	f.close() # Close the file
	print("Showing the data:")
	# Print the PageRank data
	for node, data in page_rank.items():
		print(str(node)+': '+str(data))
	print()

# Create a function for displaying the edge list
# Takes a parameter for the graph to display
def edgelist_display(G):
	print("Generating edge list...\n")
	edge_list = nx.generate_edgelist(G, data=['weight']) # Generate the edge list with weight data
	print("Writing edge list to output file...\n")
	f = open("Output Text Files\Graph_EdgeList.txt", "w") # File to store the edge list to
	# Write the edge list to the output file
	for data in edge_list:
		f.write(str(data)+'\n')
	f.close() # Close the file
	print("Showing Edge List:")
	# Display the edge list
	for line in nx.generate_edgelist(G, data=['weight']):
		print(line)
	print()

# Create a function for displaying the adjacency list
# Takes a parameter for the graph to display
def adjlist_display(G):
	print("Generating adjacency list...\n")
	adj_list = nx.generate_adjlist(G, delimiter='->') # Generate the adjacency list
	print("Writing adjacency list to output file...\n")
	f = open("Output Text Files\Graph_AdjList.txt", "w") # File to save the adjacency list to
	# Write the adjacency list to the file
	for data in adj_list:
		f.write(str(data)+'\n')
	f.close() # Close the file
	print("Showing the Adjacency List:")
	# Display the adjacency list
	for line in nx.generate_adjlist(G, delimiter='->'):
		print(str(line))
	print()

# Create a function to output the graph to a PNG
# Takes a parameter for the graph to output
def generate_output(G):
	pos = nx.spring_layout(G) # Generate the node layout for the graph
	# Get the edge labels (for displaying the edge weights)
	edge_lables = dict([((u, v), d['weight']) for u, v, d in G.edges(data=True)])
	# Draw the graph
	nx.draw(G, with_labels=True, node_size=1500, node_color="skyblue", pos=pos)
	# Draw edge labels (weights) for the graph
	nx.draw_networkx_edge_labels(G, pos=pos, edge_labels=edge_lables, font_size=6)
	# Save the graph to a png
	plt.savefig("graph.png")

# Create a function to check user menu input is valid
# Takes a parameter for the prompt to display
def check_menu(prompt):
	var = input(prompt) # Get the user input
	while var not in "0123456789": # Check to see if the options are valid with the menu
		print("That is not a valid input. Please try again:") # If not, tell the user
		var = input(prompt) # And get the input again
	return int(var) # Otherwise, return the integer form of the user's input

# Create a function to display the user manual
def display_manual():
	# Display the user manual #
	os.system('cls')
	print("This application is based on the NetworkX 2.2 Python library.")
	print("It makes use of 3 algorithms from NetworkX: A*, PageRank, and Triangles.")
	print("A* calculates the shortest path between two given vertices in the graph.")
	print("PageRank calculates the importance of vertices based on incoming links.")
	print("Triangles calculates the triangles formed between nodes.")
	print("Each algorithm outputs a related text file containing its results.")
	print("These files are stored in the 'Output Text Files' folder.\n")
	print("To build a graph, a text file containing tuples representing the graph data is used")
	print("A text file is read into the program and used to build the graph structure.")
	print("A text file that is used to build a graph in this way has the following format:")
	print("\t1) Data is given as a tuple representing a weighted edge between two nodes")
	print("\t2) This takes the form of: node1 node2 weight)")
	print("\t3) Each tuple is on a new line in the file")
	print("\t4) Every weight must be numeric in value")
	print("Example graph text files are given in the 'Input Graph Files' folder\n")
	print("The graph can be displayed as either an adjacency list or an edge list.")
	print("When the data is displayed in either of these formats, a text file will be created.")
	print("These text files are located in the 'Output Text Files' folder.")
	print("The graph can also be sent to a PNG file as a plotted graph.")
	print("This file is located in the root folder of this application.")

# Main function that manages all other functions
def main():
	data_graph = nx.Graph() # Create an undirected graph

	choice = -1 # Variable for menu options
	while choice != 0: # Loop until user exits the program
		# Display the menu
		print("\tWelcome to the Graph Applications Program\n")
		print("Please select an option from the menu:")
		print("1) Input graph data from a text file.")
		print("2) Display the graph as an adjacency list.")
		print("3) Display the graph as an edge list.")
		print("4) Run the A* algorithm on the graph.")
		print("5) Run the Triangles algorithm on the graph.")
		print("6) Run the PageRank algorithm on the graph.")
		print("7) Save the graph to an image file.")
		print("8) Clear the graph.")
		print("9) See the manual.")
		print("0) Exit the program.\n")

		# Get the choice from the user	
		choice = check_menu("Please enter an option from the menu: ")

		# Check what the input was and perform the corresponding action #
		# Choice is 0, exit the application
		if choice == 0:
			continue
		# Choice is 1, generate graph data from input file
		elif choice == 1:
			# Have the user enter the 
			file_name = input("Please enter the file you would like to build the graph from:\n")
			# Make sure the file is readable
			if os.access(file_name, os.R_OK) == True:
				print("Reading the file...\n")
				graph_file = open(file_name, "r") # Open the input file
				file_data = graph_file.readlines() # Read lines from input file into a list
				graph_file.close() # Close the file
				# Create a list of list containing the file data
				file_data = [line.strip().split() for line in file_data]
				# Convert the file data to proper values for the graph (weights need to be floats)
				graph_data = [[lst[0], lst[1], float(lst[2])] for lst in file_data]
				print("Adding the data to the graph...\n")
				data_graph.add_weighted_edges_from(graph_data) # Create the graph data from the file
				print("Nodes Added:")
				print(data_graph.nodes())
				print("\nEdges Added:")
				print(data_graph.edges())
				print()
			# If not, tell the user
			else:
				print("File could not be read.\n")
		# Choice is 2, display the graph as an adjacency list
		elif choice == 2:
			adjlist_display(data_graph)
		# Choice is 3, display the graph as an edge list
		elif choice == 3:
			edgelist_display(data_graph)
		# Choice is 4, run the A* algorithm on the graph
		elif choice == 4:
			# Get the start and end points, comma-separated, for the A* algorithm
			start, end = input("Please enter the start and end nodes in the form 'start,end': ").split(",")
			run_astar(data_graph, start, end) # Run the A* Algorithm
		# Choice is 5, run the Triangles algorithm on the graph
		elif choice == 5:
			run_triangles(data_graph)
		# Choice is 6, run the PageRank algorithm on the graph
		elif choice == 6:
			run_pagerank(data_graph)
		# Choice is 7, save the graph to an image file
		elif choice == 7:
			generate_output(data_graph)
		# Choice is 8, clear the data from the graph
		elif choice == 8:
			data_graph.clear()
		# Choice is 9, show the user manual
		elif choice == 9:
			display_manual()
		# Otherwise, the choice was an invalid option
		else:
			print("That was not a valid menu option.")
		
		os.system('pause')
		os.system('cls')

# Call the main function to run the program
if __name__ == "__main__": 
	main()

