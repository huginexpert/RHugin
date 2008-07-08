\name{get.edges}
\alias{get.edges}

\title{Get Edges}

\description{
List the edges in an RHugin domain object.
}

\usage{
get.edges(domain)
}

\arguments{
  \item{domain}{an RHugin domain object.}
}

\value{
a character vector with one element for each edge in the RHugin domain.  Each element is of the form \code{"parent -> child"} where \code{parent} is the name of the parent node and \code{child} is the name of the child node.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{hugin.domain}},
  \code{\link{add.node}},
  \code{\link{add.edge}}.
}

\examples{
# Create an RHugin domain
AppleTree <- hugin.domain()

# Add the nodes
add.node(AppleTree, "Sick", states = c("sick", "not sick"))
add.node(AppleTree, "Dry", states = c("dry", "not dry"))
add.node(AppleTree, "Loses", states = c("loses", "keeps"))

# Add the edges
add.edge(AppleTree, "Loses", "Sick")
add.edge(AppleTree, "Loses", "Dry")

# List the edges in AppleTree
get.edges(AppleTree)
}

\keyword{programming}


