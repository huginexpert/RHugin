\name{reverse.edge}
\alias{reverse.edge}

\title{Reverse An Edge}

\description{
Reverse the directed edge between two nodes in an RHugin domain object.
}

\usage{
reverse.edge(domain, node1, node2)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{node1}{a character vector of length one giving the name of the node in \code{domain} at one end of the edge.}
  \item{node2}{a character vector of length one giving the name of the node in \code{domain} at the other end of the edge.}
}

\details{
The edge reversal is done in such a way that the joint probability distribution defined by the modified domain is equivalent to the original domain.  In particular, \code{node1} inherits the parents of \code{node2} (except for \code{node1}) and vice-versa.

The operation is not performed if the reversal of the edge would create a directed cycle in \code{domain}.
}

\value{
a \code{NULL} value is invisibly returned.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{add.edge}},
  \code{\link{get.edges}},
  \code{\link{delete.edge}}.
}

\examples{
# Create an RHugin domain
AppleTree <- hugin.domain()

# Add the nodes
add.node(AppleTree, "Dry", states = c("yes", "no"))
add.node(AppleTree, "Loses", states = c("yes", "no"))

# Add an edge
add.edge(AppleTree, "Loses", "Dry")

# Reverse the edge
reverse.edge(AppleTree, "Dry", "Loses")

# Reverse it back
reverse.edge(AppleTree, "Dry", "Loses")
}

\keyword{programming}


