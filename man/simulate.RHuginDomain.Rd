\name{simulate.RHuginDomain}
\alias{simulate.RHuginDomain}

\title{Simulate Cases}

\description{
Simulate cases with respect to the conditional distribution for the evidence.
}

\usage{
\method{simulate}{RHuginDomain}(object, nsim = 1, seed = NULL, ...)
}

\arguments{
  \item{object}{an RHugin domain object.}
  \item{nsim}{a single integer value specifying the number of cases to simulate.}
  \item{seed}{a single positive integer value used to seed Hugin's (NOT R's) random number generator.  If \code{NULL} then the current state for the random number generator is used.}
  \item{\dots}{any additional arguments are ignored.}
}

\details{
If \code{object} is compiled, \code{simulate} computes \code{nsim} sample configurations with respect to the current distribution on the junction tree(s).  The distribution must be in sum-equilibrium with evidence incorporated in \sQuote{normal} mode.  Only propagated evidence is taken into account; unpropagated evidence and tables that have changed since the most recent propagation are ignored.

If \code{object} is not compiled, \code{simulate} computes \code{nsim} sample configurations with respect to the distribution determined by the tables associated with the nodes of \code{object}.
}

\value{
A data frame with one column for each node in the domain (\code{object}) whose rows contain the simulated cases.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/API_Manuals/}: \code{h_domain_simulate}, \code{h_node_get_sampled_state} and \code{h_node_get_sampled_value}.
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

# Simulate cases
simulate(AppleTree, nsim = 5)
}

\keyword{programming}


