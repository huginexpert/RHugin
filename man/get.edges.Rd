\name{get.edges}
\alias{get.edges}

\title{Get Edges}

\description{
List the edges in an RHugin domain.
}

\usage{
get.edges(domain)
}

\arguments{
  \item{domain}{an RHugin domain.}
}

\value{
a list with one element for each node in \sQuote{domain}.  Each element is in turn a list with a single element \sQuote{edges} which is a character vector containing the names of the node's children.  An empty character vector indicates that the node has no children.  This design is similar to the edge lists used in the \pkg{graph} package except that RHugin refers to the children by name while \pkg{graph} package uses their index.
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_node_get_children}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

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

# List the edges in apple
get.edges(apple)
}

\keyword{programming}


