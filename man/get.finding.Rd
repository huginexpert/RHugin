\name{get.finding}
\alias{get.finding}

\title{Get Entered Finding}

\description{
Retrieve entered findings from a node in an RHugin domain object.
}

\usage{
get.finding(domain, node)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{node}{a character vector of length one containing the name of the node from which the findings are to be retrieved.}
}

\value{
  a numeric vector containing the entered likelihood for each state in \code{node}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{\code{\link{set.finding}}, \code{\link{retract}}}

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

# Enter the conditional probability tables
sick.table <- get.table(AppleTree, "Sick")
sick.table[, 2] <- c(0.1, 0.9)
set.table(AppleTree, "Sick", sick.table)

dry.table <- get.table(AppleTree, "Dry")
dry.table[, 2] <- c(0.1, 0.9)
set.table(AppleTree, "Dry", dry.table)

loses.table <- get.table(AppleTree, "Loses")
loses.table[, 4] <- c(0.95, 0.05, 0.90, 0.10, 0.85, 0.15, 0.02, 0.98)
set.table(AppleTree, "Loses", loses.table)

# Compile the domain
compile(AppleTree)

# Set finding
set.finding(AppleTree, "Loses", c(1, 0))

# Get finding
get.finding(AppleTree, "Loses")
}

\keyword{programming}


