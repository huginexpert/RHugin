\name{reverse.edge}
\alias{reverse.edge}

\title{Reverse An Edge}

\description{
Reverse the directed edge between two nodes in an RHugin domain.
}

\usage{
reverse.edge(domain, node1, node2)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node1}{a character string specifying the name of the node in \code{domain} at one end of the edge.}
  \item{node2}{a character string specifying the name of the node in \code{domain} at the other end of the edge.}
}

\details{
The edge reversal is done in such a way that the joint probability distribution defined by the modified domain is equivalent to the original domain.  In particular, \code{node1} inherits the parents of \code{node2} (except for \code{node1}) and vice-versa.

The operation is not performed if the reversal of the edge would create a directed cycle in \code{domain}.
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_node_reverse_edge}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
# Create an RHugin domain
apple <- hugin.domain()

# Add nodes
add.node(apple, "Sick", states = c("yes", "no"))
add.node(apple, "Dry", states = c("yes", "no"))
add.node(apple, "Loses", states = c("yes", "no"))

# Add an edge
add.edge(apple, "Loses", "Dry")

# Reverse the edge
reverse.edge(apple, "Dry", "Loses")
}

\keyword{programming}


