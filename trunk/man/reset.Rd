\name{reset}
\alias{reset}

\title{Reset Inference Engine}

\description{
Establish the initial state of the inference engine: sum-equilibrium with no evidence incorporated.  Entered evidence is not deleted from the nodes and will be incorporated in the next propagation.
}

\usage{
reset(domain)
}

\arguments{
  \item{domain}{an RHugin domain object.}
}

\value{
a \code{NULL} value is invisibly returned.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{hugin.domain}}.
}

\examples{
}

\keyword{programming}


