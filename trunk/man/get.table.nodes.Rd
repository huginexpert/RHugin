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
  \item{node}{a character string specifying the name of a node in \code{domain}.}
}

\details{
Explain the structure of a table and how the node order corresponds.
}

\value{
a character vector containing the names of all the nodes associated with the conditional probability table of \code{node}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\examples{
demo("buildAppleTreeNetwork")

# Get the nodes associated with the CPT of the node "Loses"
get.table.nodes(AppleTree, "Loses")
}

\keyword{programming}


