\name{get.normalization.constant}
\alias{get.normalization.constant}

\title{The Normalization Constant}

\description{
Get the normalization constant from an RHugin domain object.
}

\usage{
get.normalization.constant(domain, log = FALSE)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{log}{a logical value.  If \code{TRUE} then the log of the normalization constant is returned.}
}

\value{
A single numeric value containing the (log) normalization constant for the domain.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/API_Manuals/}: \code{h_domain_get_normalization_constant} and \code{h_domain_get_log_normalization_constant}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\examples{
demo("buildAppleTreeNetwork")

# Compile the domain
compile(AppleTree)

# Select state
set.finding(AppleTree, "Loses", "yes")

# Propagate and get beliefs
propagate(AppleTree)
get.normalization.constant(AppleTree)
}

\keyword{programming}


