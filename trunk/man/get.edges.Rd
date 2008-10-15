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
a list with one element for each node in \sQuote{domain}.  Each element is in turn a list with a single element \sQuote{edges} which is a character vector containing the names of the node's children.  An empty character vector indicates that the node has no children.  This design is similar to the edge lists used in the \pkg{graph} package except that RHugin refers to the children by name while \pkg{graph} package uses their index.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/API_Manuals/}: \code{h_node_get_children}.
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

# List the edges in AppleTree
get.edges(AppleTree)
}

\keyword{programming}


