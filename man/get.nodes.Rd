\name{get.nodes}
\alias{get.nodes}

\title{Get Nodes}

\description{
List the nodes in an RHugin domain.
}

\usage{
get.nodes(domain)
}

\arguments{
  \item{domain}{an RHugin domain.}
}

\value{
a character vector containing the names of the nodes in the RHugin domain.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/API_Manuals/}: \code{h_domain_get_first_node}, \code{h_node_get_next} and \code{h_node_get_name}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\examples{
# Create an RHugin domain
AppleTree <- hugin.domain()

# Add nodes
add.node(AppleTree, "Sick", states = c("yes", "no"))
add.node(AppleTree, "Dry", states = c("yes", "no"))
add.node(AppleTree, "Loses", states = c("yes", "no"))

# List the nodes in AppleTree
get.nodes(AppleTree)
}

\keyword{programming}


