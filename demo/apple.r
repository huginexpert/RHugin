# Create an RHugin domain
apple <- hugin.domain()

# Add nodes
add.node(apple, "Sick", states = c("yes", "no"))
add.node(apple, "Dry", states = c("yes", "no"))
add.node(apple, "Loses", states = c("yes", "no"))

# Add edges
add.edge(apple, "Loses", "Sick")
add.edge(apple, "Loses", "Dry")

# Enter conditional probabilities
sick.table <- get.table(apple, "Sick")
sick.table[, 2] <- c(0.1, 0.9)
set.table(apple, "Sick", sick.table)

dry.table <- get.table(apple, "Dry")
dry.table[, 2] <- c(0.1, 0.9)
set.table(apple, "Dry", dry.table)

loses.table <- get.table(apple, "Loses")
loses.table[, 4] <- c(0.95, 0.05, 0.85, 0.15, 0.90, 0.1, 0.02, 0.98)
set.table(apple, "Loses", loses.table)


