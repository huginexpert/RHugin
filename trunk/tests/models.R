library(RHugin, lib.loc = "../")


# Create an RHugin domain
applesd <- hugin.domain()

# Add nodes
add.node(applesd, "Sick", states = 0:1)
add.node(applesd, "Dry", states = 0:1)
add.node(applesd, "Loses", states = 0:1)

# Add edges
add.edge(applesd, "Loses", "Sick")
add.edge(applesd, "Loses", "Dry")

sick.model <- get.model(applesd, "Sick", character(0))
sick.model$Expression <- "Binomial (1, 0.1)"
set.model(applesd, "Sick", sick.model)

dry.model <- get.model(applesd, "Dry", character(0))
dry.model$Expression <- "Binomial (1, 0.1)"
set.model(applesd, "Dry", dry.model)

loses.model <- get.model(applesd, "Loses", c("Sick", "Dry"))
loses.model$Expression[1] <- "Binomial (1, 0.02)"
loses.model$Expression[2] <- "Binomial (1, 0.85)"
loses.model$Expression[3] <- "Binomial (1, 0.9)"
loses.model$Expression[4] <- "Binomial (1, 0.95)"
set.model(applesd, "Loses", loses.model)

all.equal(loses.model, get.model(applesd, "Loses"))


################################################################################


# Create an RHugin domain
appleds <- hugin.domain()

# Add nodes
add.node(appleds, "Sick", states = 0:1)
add.node(appleds, "Dry", states = 0:1)
add.node(appleds, "Loses", states = 0:1)

# Add edges
add.edge(appleds, "Loses", "Sick")
add.edge(appleds, "Loses", "Dry")

sick.model <- get.model(appleds, "Sick", character(0))
sick.model$Expression <- "Binomial (1, 0.1)"
set.model(appleds, "Sick", sick.model)

dry.model <- get.model(appleds, "Dry", character(0))
dry.model$Expression <- "Binomial (1, 0.1)"
set.model(appleds, "Dry", dry.model)

loses.model <- get.model(appleds, "Loses", c("Dry", "Sick"))
loses.model$Expression[1] <- "Binomial (1, 0.02)"
loses.model$Expression[2] <- "Binomial (1, 0.9)"
loses.model$Expression[3] <- "Binomial (1, 0.85)"
loses.model$Expression[4] <- "Binomial (1, 0.95)"
set.model(appleds, "Loses", loses.model)

all.equal(loses.model, get.model(appleds, "Loses"))


################################################################################


generate.table(applesd, "Loses")
sd.table <- get.table(applesd, "Loses")
print(sd.table)

generate.table(appleds, "Loses")
ds.table <- get.table(appleds, "Loses")
print(ds.table)

all.equal(sd.table, ds.table)


