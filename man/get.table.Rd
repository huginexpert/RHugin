\name{get.table}
\alias{get.table}

\title{Get Table}

\description{
Get the conditional probability table (CPT) associated with a node.
}

\usage{
get.table(domain, node, class = c("data.frame", "table", "ftable"))
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{node}{a character string specifying the name of a node in \code{domain}.}
  \item{class}{a character string specifying the class of the returned table.}
}

\details{
Explain the structure of the table (once finalized).
}

\value{
depending on the value of the \code{class} argument either (1, default) a data frame with one factor column for each node associated with the table and a numeric column containing the table probabilities or frequencies (modeled on the housing data in the MASS package), (2) a table or (3) a flat table.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{hugin.domain}},
  \code{\link{get.table.nodes}},
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
get.table(AppleTree, "Loses")
}

\keyword{programming}


