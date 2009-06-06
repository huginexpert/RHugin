library(RHugin, lib.loc = "../")
limid <- hugin.domain()

add.node(limid, "Sick", states = c("yes", "no"))
add.node(limid, "Dry", states = c("yes", "no"))
add.node(limid, "Loses", states = c("yes", "no"))

add.edge(limid, "Loses", "Sick")
add.edge(limid, "Loses", "Dry")


add.node(limid, "Sick1", states = c("yes", "no"))
add.node(limid, "Dry1", states = c("yes", "no"))
add.node(limid, "Loses1", states = c("yes", "no"))

add.edge(limid, "Loses1", "Sick1")
add.edge(limid, "Loses1", "Dry1")
add.edge(limid, "Sick1", "Sick")
add.edge(limid, "Dry1", "Dry")

add.node(limid, "Harv", category = "utility")
add.edge(limid, "Harv", "Sick1")

add.node(limid, "Treat", category = "decision", states = c("treat", "not"))
add.node(limid, "Profit", category = "utility")

add.edge(limid, "Profit", "Treat")
add.edge(limid, "Sick1", "Treat")
add.edge(limid, "Treat", "Loses")


Harv.table <- get.table(limid, "Harv")
Harv.table[["Utility"]] <- c(3000, 20000)
set.table(limid, "Harv", Harv.table)

Profit.table <- get.table(limid, "Profit")
Profit.table[["Utility"]] <- c(-8000, 0)
set.table(limid, "Profit", Profit.table)


Sick.table <- get.table(limid, "Sick")
Sick.table[["Freq"]] <- c(0.1, 0.9)
set.table(limid, "Sick", Sick.table)

Dry.table <- get.table(limid, "Dry")
Dry.table[["Freq"]] <- c(0.1, 0.9)
set.table(limid, "Dry", Dry.table)

Loses.table <- get.table(limid, "Loses")
Loses.table[["Freq"]] <- c(0.95, 0.05, 0.85, 0.15, 0.90, 0.1, 0.02, 0.98)
set.table(limid, "Loses", Loses.table)


Sick1.table <- get.table(limid, "Sick1")
Sick1.table[["Freq"]] <- c(0.2, 0.8, 0.01, 0.99, 0.99, 0.01, 0.02, 0.98)
set.table(limid, "Sick1", Sick1.table)

Dry1.table <- get.table(limid, "Dry1")
Dry1.table[["Freq"]] <- c(0.6, 0.4, 0.05, 0.95)
set.table(limid, "Dry1", Dry1.table)

Loses1.table <- get.table(limid, "Loses1")
Loses1.table[["Freq"]] <- c(0.95, 0.05, 0.85, 0.15, 0.90, 0.1, 0.02, 0.98)
set.table(limid, "Loses1", Loses1.table)


compile(limid)
set.finding(limid, "Loses", "yes")
propagate(limid)

get.utility(limid, "Treat")
