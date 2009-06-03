\name{get.belief}
\alias{get.belief}

\title{Retrieve Beliefs}

\description{
Retrieve beliefs from a node in an RHugin domain object.
}

\usage{
get.belief(domain, node, states = NULL)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{node}{a character string specifying the name of the node from which the beliefs are to be retrieved.}
  \item{states}{an optional vector specifying the states of \sQuote{node} for which beliefs are to be retrieved.  If \code{NULL} then beliefs are retrieved for all states.  This argument is ignored if \code{node} is continuous.}
}

\value{
for discrete nodes: a numeric vector containing the beliefs in the specified states; for continuous nodes: a numeric vector of length two containing the mean and the variance of the marginal distribution.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/API_Manuals/}: \code{h_node_get_belief}, \code{h_node_get_mean} and \code{h_node_get_variance}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\examples{
demo("buildAppleTreeNetwork", echo = FALSE)

# Compile the domain
compile(AppleTree)

# Select state
set.finding(AppleTree, "Loses", "yes")

# Propagate and get beliefs
propagate(AppleTree)
get.belief(AppleTree, "Sick")
}

\keyword{programming}


