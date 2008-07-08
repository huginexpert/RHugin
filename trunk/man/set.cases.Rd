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
# Create a Hugin domain
ChestClinic <- hugin.domain()

# Add nodes
add.node(ChestClinic, "Asia", states = c("yes", "no"))
add.node(ChestClinic, "Smoking", states = c("yes", "no"))
add.node(ChestClinic, "Tuberculosis", states = c("yes", "no"))
add.node(ChestClinic, "LungCancer", states = c("yes", "no"))
add.node(ChestClinic, "Bronchitis", states = c("yes", "no"))
add.node(ChestClinic, "Either", states = c("yes", "no"))
add.node(ChestClinic, "XRay", states = c("yes", "no"))
add.node(ChestClinic, "Dyspnoea", states = c("yes", "no"))


# Add edges
add.edge(ChestClinic, "Tuberculosis", "Asia")
add.edge(ChestClinic, "LungCancer", "Smoking")
add.edge(ChestClinic, "Bronchitis", "Smoking")
add.edge(ChestClinic, "Either", "Tuberculosis")
add.edge(ChestClinic, "Either", "LungCancer")
add.edge(ChestClinic, "XRay", "Either")
add.edge(ChestClinic, "Dyspnoea", "Either")
add.edge(ChestClinic, "Dyspnoea", "Bronchitis")

# The cases from example 11.1 in the Hugin API Manual
ChestClinic.dat <- data.frame(
  Asia = c("yes", "no", "no", "no", "yes", "yes", "yes", "no"),
  Smoking = c("no", "yes", "yes", "no", "yes", "no", "yes", "no"),
  Dyspnoea = c("no", "yes", "yes", "yes", NA, "no", "yes", "no"),
  XRay = c("no", "no", "yes", "yes", "no", NA, "yes", NA),
  Counts = c(1, 1, 1, 1, 2, 1, 1, 1),
  stringsAsFactors = FALSE)

# Add cases
set.cases(ChestClinic, ChestClinic.dat, "Counts")
}

\keyword{programming}


