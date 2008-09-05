\name{set.cases}
\alias{set.cases}

\title{Set Cases}

\description{
Set cases in an RHugin domain object.
}

\usage{
set.cases(domain, data, counts)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{data}{a data frame.}
  \item{counts}{a numeric vector of positive values giving the multiplicity of each row of the data frame.  Alternatively \code{counts} may be the name of a variable in \code{data} containing this information.  If \code{counts} is not specified, \code{counts = 1} is assumed.}
}

\details{
The case counts need not be integers.  
}

\value{
a \code{NULL} value is invisibly returned.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{get.cases}}.
}

\examples{
demo("buildChestClinicNetwork")

# The cases from example 11.1 in the Hugin API Manual
ChestClinic.dat <- data.frame(
  Asia = c("yes", "no", "no", "no", "yes", "yes", "yes", "no"),
  Smoking = c("no", "yes", "yes", "no", "yes", "no", "yes", "no"),
  Dyspnoea = c("no", "yes", "yes", "yes", NA, "no", "yes", "no"),
  XRay = c("no", "no", "yes", "yes", "no", NA, "yes", NA),
  Freq = c(1, 1, 1, 1, 2, 1, 1, 1))

# Add cases
set.cases(ChestClinic, ChestClinic.dat, "Freq")
}

\keyword{programming}


