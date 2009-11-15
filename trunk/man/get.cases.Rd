\name{get.cases}
\alias{get.cases}

\title{Get Cases}

\description{
Retrieve case data from an RHugin domain.
}

\usage{
get.cases(domain)
}

\arguments{
  \item{domain}{an RHugin domain.}
}

\details{
If any of the cases has frequency other than one then a column named \code{Freq} containing the frequency of each case is appended to the output data frame.  If \code{domain} contains a node named \code{Freq} there will be a conflict of names.  
}

\value{
A data frame containing the cases from the specified domain.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/API_Manuals/}: \code{h_node_get_case_state}, \code{h_node_get_case_value} and \code{h_domain_get_case_count}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\examples{
demo("buildChestClinicNetwork", echo = FALSE)

# The cases from example 11.1 in the Hugin API Manual
ChestClinic.dat <- data.frame(
  Asia = c("yes", "no", "no", "no", "yes", "yes", "yes", "no"),
  Smoking = c("no", "yes", "yes", "no", "yes", "no", "yes", "no"),
  Dyspnoea = c("no", "yes", "yes", "yes", NA, "no", "yes", "no"),
  XRay = c("no", "no", "yes", "yes", "no", NA, "yes", NA),
  Freq = c(1, 1, 1, 1, 2, 1, 1, 1))

# Set cases
set.cases(ChestClinic, ChestClinic.dat, "Freq")

# Get cases
get.cases(ChestClinic)
}

\keyword{programming}


