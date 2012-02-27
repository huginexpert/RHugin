\name{get.entropy}
\alias{get.entropy}

\title{Get Entropy}

\description{
Compute the entropy of a node or the mutual information between a pair of nodes in an RHugin domain.
}

\usage{
get.entropy(domain, node, other = NULL)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node}{a character vector specifying the nodes for which to compute the entropy.}
  \item{other}{optional. If \code{NULL} (the default) then the entropy is computed for each node specified in \code{node}. Alternatively, a character vector the same length as \code{node} in which case the mutual information between \code{node[i]} and \code{other[i]} is computed.}
}

\details{
The computations are done with respect to the (joint) distribution computed by the most recent propagation (requires sum-equilibrium and normal evidence incorporation mode).
}

\value{
  a numeric vector containing the entropy or mutual information for the specified nodes.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_node_get_entropy} and \code{h_node_get_mutual_information}.
}

\author{Kjell Konis \email{kjell.konis@me.com}}

\examples{
demo("asia", echo = FALSE)
compile(asia)
set.finding(asia, "Asia", "yes")
propagate(asia)

# Get entropy
get.entropy(asia, "Smoking")

# Get mutual information
get.entropy(asia, "Smoking", "Asia")
}

\keyword{programming}


