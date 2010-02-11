\name{get.conflict}
\alias{get.conflict}

\title{Conflict of Evidence}

\description{
For \eqn{n} items of evidence, \eqn{e_{1}, \dots, e_{n}}, compute the conflict of evidence measure given by \deqn{\frac{P(e_{1}) \times \dots \times P(e_{n})}{P(e_{1}, \dots, e_{n})}.}
}

\usage{
get.conflict(domain)
}

\arguments{
  \item{domain}{an RHugin domain.}
}

\details{
The current implementation in Hugin does not support the calculation of conflict of evidence for LIMIDs. Conditional Gaussian nodes with evidence are also not supported.
}

\value{
a single numeric value containing the conflict value. If propagation has not been performed then this value will be one. If an error occurs a negative value is returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/API_Manuals/}: \code{h_domain_get_conflict}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\examples{
demo("buildChestClinicNetwork", echo = FALSE)

compile(ChestClinic)
set.finding(ChestClinic, "Dyspnoea", "yes")
set.finding(ChestClinic, "XRay", "yes")
propagate(ChestClinic)

get.conflict(ChestClinic)
}

\keyword{programming}
