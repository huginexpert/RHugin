# Create a Hugin domain
asia <- hugin.domain()

# Add nodes
nodes <- c("Asia", "Smoking", "Tuberculosis", "LungCancer",
            "Bronchitis", "Either", "XRay", "Dyspnoea")
for(node in nodes)
  add.node(asia, node, states = c("yes", "no"))

# Add edges
add.edge(asia, "Tuberculosis", "Asia")
add.edge(asia, "LungCancer", "Smoking")
add.edge(asia, "Bronchitis", "Smoking")
add.edge(asia, "Either", c("Tuberculosis", "LungCancer"))
add.edge(asia, "XRay", "Either")
add.edge(asia, "Dyspnoea", c("Either", "Bronchitis"))

# Enter conditional probabilities
cpt <- get.table(asia, "Asia")
cpt$Freq <- c(0.01, 0.99)
set.table(asia, "Asia", cpt)

cpt <- get.table(asia, "Smoking")
cpt$Freq <- c(0.5, 0.5)
set.table(asia, "Smoking", cpt)

cpt <- get.table(asia, "Tuberculosis")
cpt$Freq <- c(0.05, 0.95, 0.01, 0.99)
set.table(asia, "Tuberculosis", cpt)

cpt <- get.table(asia, "LungCancer")
cpt$Freq <- c(0.1, 0.9, 0.01, 0.99)
set.table(asia, "LungCancer", cpt)

cpt <- get.table(asia, "Bronchitis")
cpt$Freq <- c(0.6, 0.4, 0.3, 0.7)
set.table(asia, "Bronchitis", cpt)

cpt <- get.table(asia, "Either")
cpt$Freq <- c(1, 0, 1, 0, 1, 0, 0, 1)
set.table(asia, "Either", cpt)

cpt <- get.table(asia, "XRay")
cpt$Freq <- c(0.98, 0.02, 0.05, 0.95)
set.table(asia, "XRay", cpt)

cpt <- get.table(asia, "Dyspnoea")
cpt$Freq <- c(0.9, 0.1, 0.8, 0.2, 0.7, 0.3, 0.1, 0.9)
set.table(asia, "Dyspnoea", cpt)

