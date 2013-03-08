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
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_domain_get_first_node}, \code{h_node_get_next} and \code{h_node_get_name}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
# Create an RHugin domain
apple <- hugin.domain()

# Add nodes
add.node(apple, "Sick", states = c("yes", "no"))
add.node(apple, "Dry", states = c("yes", "no"))
add.node(apple, "Loses", states = c("yes", "no"))

# List the nodes in apple
get.nodes(apple)
}

\keyword{programming}


