library(RHugin, lib.loc = "../")
asia <- hugin.domain()

nodes <- c("Asia", "Smoking", "Tuberculosis", "LungCancer",
            "Bronchitis", "Either", "XRay", "Dyspnoea")
for(node in nodes)
  add.node(asia, node, states = c("yes", "no"))

add.edge(asia, "Tuberculosis", "Asia")
add.edge(asia, "LungCancer", "Smoking")
add.edge(asia, "Bronchitis", "Smoking")
add.edge(asia, "Either", c("Tuberculosis", "LungCancer"))
add.edge(asia, "XRay", "Either")
add.edge(asia, "Dyspnoea", c("Either", "Bronchitis"))

Asia.table <- get.table(asia, "Asia")
Asia.table[["Freq"]] <- c(0.01, 0.99)
set.table(asia, "Asia", Asia.table)

Smoking.table <- get.table(asia, "Smoking")
Smoking.table[["Freq"]] <- c(0.5, 0.5)
set.table(asia, "Smoking", Smoking.table)

Tuberculosis.table <- get.table(asia, "Tuberculosis")
Tuberculosis.table[["Freq"]] <- c(0.05, 0.95, 0.01, 0.99)
set.table(asia, "Tuberculosis", Tuberculosis.table)

LungCancer.table <- get.table(asia, "LungCancer")
LungCancer.table[["Freq"]] <- c(0.1, 0.9, 0.01, 0.99)
set.table(asia, "LungCancer", LungCancer.table)

Bronchitis.table <- get.table(asia, "Bronchitis")
Bronchitis.table[["Freq"]] <- c(0.6, 0.4, 0.3, 0.7)
set.table(asia, "Bronchitis", Bronchitis.table)

Either.table <- get.table(asia, "Either")
Either.table[["Freq"]] <- c(1, 0, 1, 0, 1, 0, 0, 1)
set.table(asia, "Either", Either.table)

XRay.table <- get.table(asia, "XRay")
XRay.table[["Freq"]] <- c(0.98, 0.02, 0.05, 0.95)
set.table(asia, "XRay", XRay.table)

Dyspnoea.table <- get.table(asia, "Dyspnoea")
Dyspnoea.table[["Freq"]] <- c(0.9, 0.1, 0.8, 0.2, 0.7, 0.3, 0.1, 0.9)
set.table(asia, "Dyspnoea", Dyspnoea.table)

compile(asia)

set.finding(asia, "Asia", "yes")
set.finding(asia, "Dyspnoea", "yes")

propagate(asia)

get.belief(asia, "Asia")
get.belief(asia, "Smoking")
get.belief(asia, "Tuberculosis")
get.belief(asia, "LungCancer")
get.belief(asia, "Bronchitis")
get.belief(asia, "Either")
get.belief(asia, "XRay")
get.belief(asia, "Dyspnoea")


