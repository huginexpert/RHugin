\name{write.cases}
\alias{write.cases}
\alias{read.cases}

\title{Read/Write Data Files}

\description{
Write the current cases to a data file or read cases from a data file.
}

\usage{
write.cases(domain, filename, nodes)
read.cases(domain, filename)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{filename}{a character string.}
  \item{nodes}{a character vector specifying the names of the nodes whose cases should be written to the data file.  If omitted, cases for all of the nodes in \code{domain} will be written.}
}

\details{
This function is provided to facilitate sharing cases between Hugin front-ends (e.g., the Hugin GUI).  The \code{\link{set.cases}} and \code{\link{get.cases}} functions are recommend for working with cases in R.
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_domain_save_cases} and \code{h_domain_parse_cases}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\examples{
demo("asia", echo = FALSE)

# The cases from example 11.1 in the Hugin API Manual
asia.dat <- data.frame(
  Asia = c("yes", "no", "no", "no", "yes", "yes", "yes", "no"),
  Smoking = c("no", "yes", "yes", "no", "yes", "no", "yes", "no"),
  Dyspnoea = c("no", "yes", "yes", "yes", NA, "no", "yes", "no"),
  XRay = c("no", "no", "yes", "yes", "no", NA, "yes", NA),
  Freq = c(1, 1, 1, 1, 2, 1, 1, 1))

# Set cases
set.cases(asia, asia.dat, "Freq")

# Write cases to a data file
write.cases(asia, filename = "asia.txt",
            nodes = c("Asia", "Smoking", "Dyspnoea", "XRay"))

# Read cases from a data file
read.cases(asia, filename = "asia.txt")
}

\keyword{programming}


