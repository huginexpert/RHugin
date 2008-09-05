# Create a Hugin domain
ChestClinic <- hugin.domain()

# Add nodes
nodes <- c("Asia", "Smoking", "Tuberculosis", "LungCancer",
            "Bronchitis", "Either", "XRay", "Dyspnoea")
for(node in nodes)
  add.node(ChestClinic, node, states = c("yes", "no"))

# Add edges
add.edge(ChestClinic, "Tuberculosis", "Asia")
add.edge(ChestClinic, "LungCancer", "Smoking")
add.edge(ChestClinic, "Bronchitis", "Smoking")
add.edge(ChestClinic, "Either", c("Tuberculosis", "LungCancer"))
add.edge(ChestClinic, "XRay", "Either")
add.edge(ChestClinic, "Dyspnoea", c("Either", "Bronchitis"))

# Enter conditional probabilities
cpt <- get.table(ChestClinic, "Asia")
cpt$Freq <- c(0.01, 0.99)
set.table(ChestClinic, "Asia", cpt)

cpt <- get.table(ChestClinic, "Smoking")
cpt$Freq <- c(0.5, 0.5)
set.table(ChestClinic, "Smoking", cpt)

cpt <- get.table(ChestClinic, "Tuberculosis")
cpt$Freq <- c(0.05, 0.95, 0.01, 0.99)
set.table(ChestClinic, "Tuberculosis", cpt)

cpt <- get.table(ChestClinic, "LungCancer")
cpt$Freq <- c(0.1, 0.9, 0.01, 0.99)
set.table(ChestClinic, "LungCancer", cpt)

cpt <- get.table(ChestClinic, "Bronchitis")
cpt$Freq <- c(0.6, 0.4, 0.3, 0.7)
set.table(ChestClinic, "Bronchitis", cpt)

cpt <- get.table(ChestClinic, "Either")
cpt$Freq <- c(1, 0, 1, 0, 1, 0, 0, 1)
set.table(ChestClinic, "Either", cpt)

cpt <- get.table(ChestClinic, "XRay")
cpt$Freq <- c(0.98, 0.02, 0.05, 0.95)
set.table(ChestClinic, "XRay", cpt)

cpt <- get.table(ChestClinic, "Dyspnoea")
cpt$Freq <- c(0.9, 0.1, 0.8, 0.2, 0.7, 0.3, 0.1, 0.9)
set.table(ChestClinic, "Dyspnoea", cpt)

