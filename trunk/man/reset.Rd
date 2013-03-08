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
  \item{domain}{an RHugin domain.}
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_domain_reset_inference_engine}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\keyword{programming}


