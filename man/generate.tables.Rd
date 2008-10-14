\name{generate.tables}
\alias{generate.tables}

\title{Generate Tables}

\description{
Generate conditional probability tables (CPT) for a domain from a data frame.
}

\usage{
generate.tables(domain, data, nodes = NULL)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{data}{a data frame with columns corresponding to the nodes in \code{domain}.}
  \item{nodes}{an optional character vector of node names in \code{domain}.  If present, conditional probability tables are only generated for these nodes.}
}

\value{
a \code{NULL} value is invisibly returned.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\examples{
library(MASS)
data(housing)

# Create an empty RHugin domain
hd <- hugin.domain()

# Generate nodes for the housing data
generate.nodes(hd, housing)

# Add edges
add.edge(hd, "Cont", "Type")
add.edge(hd, "Sat", "Infl")
add.edge(hd, "Sat", "Type")
add.edge(hd, "Sat", "Cont")

# Generate conditional probability tables
generate.tables(hd, housing)
}

\keyword{programming}


