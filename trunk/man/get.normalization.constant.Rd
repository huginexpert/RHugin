\name{get.normalization.constant}
\alias{get.normalization.constant}

\title{Get Normalization Constant}

\description{
Retrieve the normalization constant from an RHugin domain.
}

\usage{
get.normalization.constant(domain, log = FALSE)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{log}{a logical value.  If \code{TRUE} then the log of the normalization constant is returned.}
}

\value{
A single numeric value containing the (log) normalization constant for the domain.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_domain_get_normalization_constant} and \code{h_domain_get_log_normalization_constant}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
demo("apple", echo = FALSE)

# Compile the domain
compile(apple)

# Select state
set.finding(apple, "Loses", "yes")

# Propagate and get beliefs
propagate(apple)
get.normalization.constant(apple)
}

\keyword{programming}


