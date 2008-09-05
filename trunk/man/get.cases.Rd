\name{get.cases}
\alias{get.cases}

\title{Get Cases}

\description{
Retrieve the cases data from an RHugin domain object as a data frame.
}

\usage{
get.cases(domain)
}

\arguments{
  \item{domain}{an RHugin domain object.}
}

\details{
If any of the cases has frequency other than one then a column named \code{Freq} containing the frequency of each case is appended to the output data frame.  If \code{domain} contains a node named \code{counts} there will be a conflict of names.  
}

\value{
A data frame containing the cases from the specified domain.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{set.cases}}.
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

# Get cases
get.cases(ChestClinic)
}

\keyword{programming}


