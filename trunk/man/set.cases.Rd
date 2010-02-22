\name{set.cases}
\alias{set.cases}

\title{Set Cases}

\description{
Set cases in an RHugin domain.
}

\usage{
set.cases(domain, data, Freq)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{data}{a data frame.}
  \item{Freq}{a numeric vector of positive values giving the multiplicity of each row of the data frame.  Alternatively \code{Freq} may be the name of a variable in \code{data} containing this information.  If \code{Freq} is not specified, \code{Freq = 1} is assumed.}
}

\details{
The elements of Freq need not be integers.  
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_node_set_case_state}, \code{h_node_set_case_value} and \code{h_node_unset_case}.
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

# Add cases
set.cases(ChestClinic, ChestClinic.dat, "Freq")


# Cases for all subtypes of nodes
hd <- hugin.domain()

add.node(hd, "labeled", states = letters[1:4])
add.node(hd, "boolean", states = c(FALSE, TRUE))
add.node(hd, "numbered", states = 1:3)
add.node(hd, "interval", subtype = "interval", states = c(-Inf, -3:3, Inf))
add.node(hd, "continuous", kind = "continuous")

set.seed(2)
test.dat <- data.frame(
  labeled = sample(letters[1:3], 10, TRUE),
  boolean = sample(c(FALSE, TRUE), 10, TRUE),
  numbered = sample(1:3, 10, TRUE),
  interval = 2 * rnorm(10),
  continuous = 2 * rnorm(10)
)

set.cases(hd, test.dat)
get.cases(hd)
}

\keyword{programming}


