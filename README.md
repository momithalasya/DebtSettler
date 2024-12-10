# DebtSettler
DebtSettler simplifies financial transactions by calculating net balances and minimizing cash flow between entities. It identifies the fewest transactions needed for efficient settlements, reducing complexity and saving time. Ideal for banks or groups, it ensures smooth and optimized debt management.
This program minimizes cash flow in a group of banks or entities by using graphs to represent financial transactions. Here's a breakdown:

# Graph Representation:

The program uses a 2D vector (adjacency matrix) to represent the graph.
Each node corresponds to a bank, and edges represent transactions with weights as amounts owed.
# Why Graphs?

A graph is ideal for this scenario as it captures relationships (debts) between entities and allows for efficient traversal and computation of net balances.
# Steps Involved:

# Input Handling:
Bank names, transactions, and amounts are taken as input. Bank names are stored in a vector, and their indices are mapped using a hash map for quick lookup.
Net Balances Calculation: The net amount each entity owes or is owed is computed by summing incoming and outgoing edges for each node.
# Cash Flow Minimization:
Using recursive logic, the program identifies the entity with the highest credit and debit, settles the smallest possible amount between them, and repeats until all debts are cleared.
# Output:

The program displays the optimized set of transactions needed to settle all debts with minimal cash flow.
This approach ensures efficiency and simplicity in managing complex financial relationships using fundamental graph concepts.
