\name{get.table.nodes}
\alias{get.table.nodes}

\title{Get Table Nodes}

\description{
Get the nodes associated with the conditional probability table of a node.
}

\usage{
get.table.nodes(domain, node)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{node}{a character vector of length one containing the name of a node in \code{domain}.}
}

\details{
Explain the structure of a table and how the node order corresponds.
}

\value{
a character vector containing the names of all the nodes associated with the conditional probability table of \code{node}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{hugin.domain}},
  \code{\link{get.table}},
  \code{\link{set.table}}.
}

\examples{
# Create an RHugin domain
AppleTree <- hugin.domain()

# Add the nodes
add.node(AppleTree, "Sick", states = c("yes", "no"))
add.node(AppleTree, "Dry", states = c("yes", "no"))
add.node(AppleTree, "Loses", states = c("yes", "no"))

# Add the edges
add.edge(AppleTree, "Loses", "Sick")
add.edge(AppleTree, "Loses", "Dry")

# Set the conditional probability tables
sick.table <- get.table(AppleTree, "Sick")
sick.table[, 2] <- c(0.1, 0.9)
set.table(AppleTree, "Sick", sick.table)

dry.table <- get.table(AppleTree, "Dry")
dry.table[, 2] <- c(0.1, 0.9)
set.table(AppleTree, "Dry", dry.table)

loses.table <- get.table(AppleTree, "Loses")
loses.table[, 4] <- c(0.95, 0.05, 0.90, 0.10, 0.85, 0.15, 0.02, 0.98)
set.table(AppleTree, "Loses", loses.table)

# Get the nodes associated with the CPT of the node "Loses"
get.table.nodes(AppleTree, "Loses")
}

\keyword{programming}


