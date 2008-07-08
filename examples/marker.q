
## First create a domain ##

marker <- hugin.domain()

## Then add the nodes ##

add.node(marker, "pfpg", states = as.character(8:14))
add.node(marker, "pfmg", states = as.character(8:14))
add.node(marker, "mpg", states = as.character(8:14))
add.node(marker, "mmg", states = as.character(8:14))
add.node(marker, "tfpg", states = as.character(8:14))
add.node(marker, "tfmg", states = as.character(8:14))
add.node(marker, "cpg", states = as.character(8:14))
add.node(marker, "cmg", states = as.character(8:14))

states <- paste(rep(8:14, 7:1), unlist(sapply(8:14, function(u) u:14)), sep = ",")
add.node(marker, "pfgt", states = states)
add.node(marker, "mgt", states = states)
add.node(marker, "cgt", states = states)

add.node(marker, "tfpf", states = c("yes", "no"))

## Then add the edges ##

add.edge(marker, "pfgt", "pfpg")
add.edge(marker, "pfgt", "pfmg")

add.edge(marker, "tfpg", "pfpg")
add.edge(marker, "tfpg", "tfpf")

add.edge(marker, "tfmg", "pfmg")
add.edge(marker, "tfmg", "tfpf")

add.edge(marker, "cpg", "tfpg")
add.edge(marker, "cpg", "tfmg")

add.edge(marker, "cmg", "mpg")
add.edge(marker, "cmg", "mmg")

add.edge(marker, "mgt", "mmg")
add.edge(marker, "mgt", "mpg")

add.edge(marker, "cgt", "cpg")
add.edge(marker, "cgt", "cmg")




## Put the data into the tables ##

#load("marker.RData")
nodes <- get.nodes(marker)
for(node in nodes)
  set.table(marker, node, get(paste(node, "table", sep = ".")))

## Compile the domain ##

compile(marker)

## Set evidence and get beliefs ##

pfgt.states <- get.states(marker, "pfgt")
mgt.states <- get.states(marker, "mgt")
cgt.states <- get.states(marker, "cgt")

X <- expand.grid(list(pfgt = pfgt.states, cgt = cgt.states, mgt = mgt.states))
X <- X[length(X):1]

true.mommy <- function(mgt, cgt)
{
  mgt <- strsplit(mgt, split = ",")[[1]]
  cgt <- strsplit(cgt, split = ",")[[1]]
  length(intersect(mgt,cgt)) > 0
}

keep <- apply(X[1:2], 1, function(u) true.mommy(u[1], u[2]))
X <- X[keep, ]

beliefs <- numeric(nrow(X))
norm.const <- numeric(nrow(X))

for(i in 1:nrow(X)) {
  set.finding(marker, "mgt", as.character(X[i, 1]))
  set.finding(marker, "cgt", as.character(X[i, 2]))
  set.finding(marker, "pfgt", as.character(X[i, 3]))
  propagate(marker)
  beliefs[i] <- get.belief(marker, "tfpf", "yes")
  norm.const[i] <- get.normalization.constant(marker)
  retract(marker, "mgt")
  retract(marker, "cgt")
  retract(marker, "pfgt")
  if(i %% 100 == 0) print(paste("completed", i, "iterations so far"))
}


HQE <- function(beliefs, norm.const)
{
  idx <- beliefs > 0.0 & beliefs < 1.0
  beliefs <- beliefs[idx]
  beliefs <- beliefs * log(beliefs) + (1.0 - beliefs) * log(1.0 - beliefs)
  -sum(beliefs * norm.const[idx])
}

HQE(beliefs, norm.const)
