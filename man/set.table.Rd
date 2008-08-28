\name{set.table}
\alias{set.table}

\title{Set Table}

\description{
Set the conditional probability table (CPT) of a node in an RHugin domain.
}

\usage{
set.table(domain, node, data)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{node}{a character vector of length one containing the name of a node in \code{domain}.}
  \item{data}{a data frame (see details).}
}

\details{
The data frame containing the table must match Hugin's internal representation of the table data. The best way to do this is to use \code{get.table} to obtain a data frame with the proper layout, set the probabilities (frequencies) in the final column of this data frame and finally use \code{set.table} to set the table information in Hugin.  See the example.
}

\value{
a \code{NULL} value is invisibly returned.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{hugin.domain}},
  \code{\link{get.table.nodes}},
  \code{\link{get.table}}.
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
}

\keyword{programming}


