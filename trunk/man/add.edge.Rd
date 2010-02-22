\name{add.edge}
\alias{add.edge}

\title{Add Edge}

\description{
Add a directed edge from one or more parents.
}

\usage{
add.edge(domain, child, parent)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{child}{a character string containing the name of the child node.}
  \item{parent}{a character vector specifying by name one or more parent nodes.}
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_node_add_parent}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\examples{
# Create an RHugin domain
AppleTree <- hugin.domain()

# Add nodes
add.node(AppleTree, "Sick", states = c("yes", "no"))
add.node(AppleTree, "Dry", states = c("yes", "no"))
add.node(AppleTree, "Loses", states = c("yes", "no"))

# Add edges
add.edge(AppleTree, "Loses", "Sick")
add.edge(AppleTree, "Loses", "Dry")
}

\keyword{programming}


