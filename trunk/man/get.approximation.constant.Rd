\name{get.approximation.constant}
\alias{get.approximation.constant}

\title{Get Approximation Constant}

\description{
Retrieve the approximation constant from the most recent (explicit or implicit) approximation operation.
}

\usage{
get.approximation.constant(domain)
}

\arguments{
  \item{domain}{an RHugin domain.}
}

\details{
Compiling \code{domain} with approximation (explicit approximation) eliminates small probabilities from the clique potentials. The annihilation of these small probabilities within the clique potentials can be thought of as entering a special kind of evidence. As part of the approximation process, this evidence is propagated throughout the junction trees, thereby reaching an equilibrium state on all junction trees. The joint probability of the evidence is the approximation constant.

An implicit approximation takes place when one or more of the conditional probability tables of a compressed domain are altered and a propagation operation is performed. Since some (discrete) state configurations have been removed from a compressed domain, the probability mass of the remaining configurations will typically be less than 1; this probability mass is the approximation constant.
}

\value{
a single numeric value containing the approximation constant.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/API_Manuals/}: \code{h_domain_get_approximation_constant}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{compile.RHuginDomain}}.
}

\keyword{programming}


