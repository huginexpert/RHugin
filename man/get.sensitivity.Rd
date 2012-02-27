\name{get.sensitivity}
\alias{get.sensitivity}

\title{Compute Sensitivity}

\description{
Compute either the sensitivity constants or the sensitivity set for an output node in a belief network.
}

\usage{
get.sensitivity(domain, output, state, ..., set = FALSE)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{output}{a character string specifying the name of the output node.}
  \item{state}{a state of \code{output}.}
  \item{\dots}{one or more inputs of the form \code{node = state} where \code{node} is a node in \code{domain} and \code{state} is a state of that node.  Alternatively a list containing the inputs in this form may be provided.}
  \item{set}{a logical flag.  If \code{TRUE} then the sensitivity set is returned otherwise the sensitivity constants are returned.  The \code{\dots} argument(s) are ignored when \code{set = TRUE}.}
}

\details{
The sensitivity function is defined to be

\deqn{P(A = a|E)(x) = \frac{\alpha x + \beta}{\gamma x + \delta}}

where \eqn{E} is the evidence, \eqn{A} is the node \code{output}, \eqn{a} is a state of \eqn{output}, \eqn{\alpha}, \eqn{\beta}, \eqn{\gamma} and \eqn{\delta} are constants and \eqn{x} is the probability that the input node is in the specified state.
}

\value{
When \code{set = FALSE} a matrix with one row for each \code{\dots} argument and columns \code{alpha}, \code{beta}, \code{gamma} and \code{delta}.  Otherwise a character vector containing the names of the nodes in the sensitivity set of \code{output}.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_node_compute_sensitivity_data}, \code{h_node_get_sensitivity_constants} and \code{h_domain_get_sensitivity_set}.
}


\author{Kjell Konis \email{kjell.konis@me.com}}

\examples{
demo("asia", echo = FALSE)
compile(asia)

set.finding(asia, "Dyspnoea", "yes")
propagate(asia)

# Compute the constants for the sensitivity of a positive diagnosis on
# the population proportion of smokers.
get.sensitivity(asia, "LungCancer", "yes", Smoking = "yes")

# Compute the sensitivity set for lung cancer diagnosis.
get.sensitivity(asia, "LungCancer", "yes", set = TRUE)
}

\keyword{programming}


