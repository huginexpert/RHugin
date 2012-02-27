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

\author{Kjell Konis \email{kjell.konis@me.com}}

\examples{
# Create an RHugin domain
apple <- hugin.domain()

# Add nodes
add.node(apple, "Sick", states = c("yes", "no"))
add.node(apple, "Dry", states = c("yes", "no"))
add.node(apple, "Loses", states = c("yes", "no"))

# Add edges
add.edge(apple, "Loses", "Sick")
add.edge(apple, "Loses", "Dry")
}

\keyword{programming}


